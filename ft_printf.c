/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 00:54:15 by jtong             #+#    #+#             */
/*   Updated: 2020/12/01 13:32:57 by jtong            ###   ########.fr       */
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

	(void)flags;
	num = va_arg(input->ap, typeof(num));
	input->length += ft_putnbr_fd(num, input->fd);
	return (1);
}

int		ft_va_string(t_input *input, t_flags *flags)
{
	char	*str;

	(void)flags;
	str = va_arg(input->ap, typeof(str));
	input->length += write(input->fd, str, ft_strlen(str));
	return (1);
}

int		ft_va_char(t_input *input, t_flags *flags)
{
	char	c;

	(void)flags;
	c = va_arg(input->ap, int);
	input->length += write(input->fd, &c, 1);
	return (1);
}

int		ft_va_ull(t_input *input, t_flags *flags)
{
	unsigned long long	ull;
	char				*str;
	int					len;

	if (flags->base == 0)
		flags->base = 10;
	if (flags->length_modifier == 1)
		ull = va_arg(input->ap, unsigned long);
	else
		ull = va_arg(input->ap, unsigned int);
	str = ft_ulltoa_base(ull, flags->base);
	if (flags->capital)
	{
		len = 0;
		while (str[len])
		{
			str[len] = ft_toupper(str[len]);
			len++;
		}
	}
	len = write(input->fd, str, ft_strlen(str));
	free(str);
	input->length += len;
	return (1);
}

int		ft_va_pointer(t_input *input, t_flags *flags)
{
	void	*ptr;
	char	*str;
	int		len;

	(void)flags;
	ptr = va_arg(input->ap, typeof(ptr));
	str = ft_ulltoa_base((unsigned long long)ptr, 16);
	len = write(input->fd, str, ft_strlen(str));
	free(str);
	input->length += len;
	return (1);
}

int		ft_va_hex(t_input *input, t_flags *flags)
{
	if (flags->conversion_specifier == 7)
		flags->capital = 1;
	flags->base = 16;
	ft_va_ull(input, flags);
	return (1);
}

int		ft_va_percent(t_input *input, t_flags *flags)
{
	(void)flags;
	input->length += write(input->fd, "%", 1);
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
	flags->field_width = ft_strtol(input->format + input->index, &ptr, 10);
	input->index = ptr - input->format;
	return (0);
}

int		pf_precision(t_input *input, t_flags *flags)
{
	int		precision;
	char	*ptr;

	(void)flags;
	input->index++;
	precision = ft_strtol(input->format + input->index, &ptr, 10);
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
	size_t		i;

	i = -1;
	while (c != specifiers[i])
		i++;
	return (i);
}

/// f_func returns whether to stop parsing
size_t	parse_format(t_input *input)
{
	t_flags			flags;
	typedef int		(*f_func)(t_input *, t_flags *);
	static f_func	table[256] = {
		ft_va_char, ft_va_string, ft_va_pointer, ft_va_integer, ft_va_integer, ft_va_ull, ft_va_hex, ft_va_hex, ft_va_percent, pf_left_adjust, pf_zero_pad, pf_precision, pf_null, pf_field_width, pf_field_width, pf_field_width, pf_field_width, pf_field_width, pf_field_width, pf_field_width, pf_field_width, pf_field_width,
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
			parse_format(&input);
		}
	}
	va_end(input.ap);
	return (input.length);
}
