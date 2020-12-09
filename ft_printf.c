/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pi <pi@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 00:54:15 by jtong             #+#    #+#             */
/*   Updated: 2020/12/09 11:08:41 by pi               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include "ft_printf.h"
#include "libft.h"

int		ft_va_integer(t_input *input, t_flags *flags)
{
	int		num;

	num = va_arg(input->ap, typeof(num));
	if (num >= 0)
	{
		if (flags->sign_space)
			flags->prefix = " ";
		else if (flags->sign_always)
			flags->prefix = "+";
	}
	flags->output = ft_itoa(num);
	return (1);
}

int		ft_va_string(t_input *input, t_flags *flags)
{
	char	*str;

	(void)flags;
	str = va_arg(input->ap, typeof(str));
	flags->output = ft_strdup(str);
	return (1);
}

int		ft_va_char(t_input *input, t_flags *flags)
{
	char	c;

	(void)flags;
	c = va_arg(input->ap, int);
	flags->output = ft_strsub(&c, 0, 1);
	return (1);
}

int		ft_va_ull(t_input *input, t_flags *flags)
{
	unsigned long long	ull;
	int					len;

	if (flags->base == 0)
		flags->base = 10;
	if (flags->length_modifier == 1 || flags->conversion_specifier == 2)
		ull = va_arg(input->ap, unsigned long long);
	else if (flags->length_modifier == 1)
		ull = va_arg(input->ap, unsigned long);
	else
		ull = va_arg(input->ap, unsigned int);
	flags->output = ft_ulltoa_base(ull, flags->base);
	if (flags->capital)
	{
		len = 0;
		while (flags->output[len])
		{
			flags->output[len] = ft_toupper(flags->output[len]);
			len++;
		}
	}
	return (1);
}

int		ft_va_hex(t_input *input, t_flags *flags)
{
	if (flags->conversion_specifier == 7)
		flags->capital = 1;
	if (flags->alternate)
	{
		if (flags->capital)
			flags->prefix = "0X";
		else
			flags->prefix = "0x";
	}
	flags->base = 16;
	ft_va_ull(input, flags);
	return (1);
}

int		ft_va_pointer(t_input *input, t_flags *flags)
{
	void	*ptr;

	flags->prefix = "0x";
	flags->base = 16;
	ptr = va_arg(input->ap, typeof(ptr));
	flags->output = ft_ulltoa_base((unsigned long long)ptr, flags->base);
	return (1);
}

int		ft_va_percent(t_input *input, t_flags *flags)
{
	(void)input;
	flags->field_width = 0;
	flags->output = ft_strdup("%");
	return (1);
}

int		pf_left_adjust(t_input *input, t_flags *flags)
{
	(void)input;
	flags->left_adjust = 1;
	return (0);
}

int		pf_zero_pad(t_input *input, t_flags *flags)
{
	(void)input;
	flags->zero_pad = 1;
	return (0);
}

int		pf_field_width(t_input *input, t_flags *flags)
{
	char	*ptr;

	// if * then va_arg next arg
	if (input->format[input->index] == '*')
	{
		flags->field_width = va_arg(input->ap, int);
		input->index++;
	}
	else
	{
		flags->field_width = ft_strtol(input->format + input->index, &ptr, 10);
		input->index = ptr - input->format - 1;
	}
	return (0);
}

int		pf_precision(t_input *input, t_flags *flags)
{
	char	*ptr;

	input->index++;
	if (input->format[input->index] == '*')
	{
		flags->field_width = va_arg(input->ap, int);
		input->index++;
	}
	else
	{
		flags->precision = ft_strtol(input->format + input->index, &ptr, 10);
		input->index = ptr - input->format - 1;
	}
	return (0);
}

int		pf_null(t_input *input, t_flags *flags)
{
	(void)input;
	(void)flags;
	return (0);
}

int		get_id(char c)
{
	static char	*specifiers = "cspdiuxX%-0.*123456789";
	int		i;

	i = 0;
	while (specifiers[i] && c != specifiers[i])
		i++;
	if (!specifiers[i])
		return (-1);
	return (i);
}

void	print(t_input *input, t_flags *flags)
{
	char	pad;
	int		padding;

	if (!flags->output)
		return;
	pad = ' ';
	if (flags->zero_pad)
		pad = '0';
	if (flags->output)
		flags->outputlen = ft_strlen(flags->output);
	if (flags->prefix)
		flags->prefixlen = ft_strlen(flags->prefix);
	padding = flags->field_width - (flags->outputlen + flags->prefixlen);
	if (!flags->left_adjust)
		while (padding-- > 0)
			input->length += write(input->fd, &pad, 1);
	input->length += write(input->fd, flags->prefix, flags->prefixlen);
	input->length += write(input->fd, flags->output, flags->outputlen);
	free(flags->output);
	if (flags->left_adjust)
		while (padding-- > 0)
			input->length += write(input->fd, &pad, 1);
}

/// f_func returns whether to stop parsing
int		parse_format(t_input *input)
{
	t_flags			flags;
	typedef int		(*f_func)(t_input *, t_flags *);
	static f_func	table[256] = {
		ft_va_char, ft_va_string, ft_va_pointer, ft_va_integer, ft_va_integer, ft_va_ull, ft_va_hex, ft_va_hex, ft_va_percent, pf_left_adjust, pf_zero_pad, pf_precision, pf_field_width, pf_field_width, pf_field_width, pf_field_width, pf_field_width, pf_field_width, pf_field_width, pf_field_width, pf_field_width, pf_field_width,
	};
	int				id;

	flags = (t_flags){0};
	id = -1;
	while (input->format[input->index]
		&& (id = get_id(input->format[input->index])) != -1)
	{
		flags.conversion_specifier = id;
		if ((*table[id])(input, &flags))
		{
			input->index++;
			break;
		}
		id = -1;
		input->index++;
	}
	if (id == -1)
	{
		free(flags.output);
		return (-1);
	}
	print(input, &flags);
	return (0);
}

int		ft_printf(const char *format, ...)
{
	t_input	input;
	int		start;

	input = (t_input){};
	va_start(input.ap, format);
	if (format == NULL)
		return (0);
	input.format = format;
	input.index = 0;
	while (input.format[input.index])
	{
		start = input.index; 
		while (input.format[input.index] && input.format[input.index] != '%')
			input.index++;
		input.length += write(input.fd, input.format + start, input.index - start);
		if (input.format[input.index] == '%')
		{
			input.index++;
			if (parse_format(&input))
				return (-1);
		}
	}
	va_end(input.ap);
	return (input.length);
}
