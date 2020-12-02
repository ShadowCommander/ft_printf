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

int		ft_va_integer(t_input *input, t_flags *flags)
{
	int		num;
	char	*str;
	int		len;

	num = va_arg(input->ap, typeof(num));
	str = ft_itoa(num);
	len = write(input->fd, str, ft_strlen(str));
	free(str);
	return (len);
}

int		ft_va_string(t_input *input, t_flags *flags)
{
	char	*str;

	str = va_arg(input->ap, typeof(str));
	return (write(input->fd, str, ft_strlen(str)));
}

int		ft_va_char(t_input *input, t_flags *flags)
{
	char	c;

	c = va_arg(input->ap, typeof(c));
	return (write(input->fd, &c, 1));
}


int		ft_va_ull(t_input *input, t_flags *flags)
{
	unsigned long long	*ull;
	char				*str;
	int					len;

	ull = va_arg(input->ap, typeof(ull));
	str = ft_ulltoa_base(ull, flags->base);
	len = write(input->fd, str, ft_strlen(str));
	free(str);
	return (len);
}

int		ft_va_pointer(t_input *input, t_flags *flags)
{
	void	*ptr;
	char	*str;
	int		len;

	ptr = va_arg(input->ap, typeof(ptr));
	str = ft_ulltoa_base(ptr, 16);
	len = write(input->fd, str, ft_strlen(str));
	free(str);
	return (len);
}

int		ft_va_hex(t_input *input, t_flags *flags)
{
	if (flags->conversion_specifier == 'X')
		flags->capital = 1;
	flags->base = 8;
	return (ft_va_ull(input, flags));
}

int		ft_va_percent(t_input *input, t_flags *flags)
{
	return (write(input->fd, "%", 1));
}

int		pf_left_adjust(t_input *input, t_flags *flags)
{
	flags->left_adjust = 1;
	return (0);
}

int		pf_zero_pad(t_input *input, t_flags *flags)
{
	flags->zero_pad = 1;
	return (0);
}

int		pf_field_width(t_input *input, t_flags *flags)
{
	char	*ptr;

	flags->field_width = ft_strtol(input->format + input->index, &ptr, 10);
	return (0);
}

int		pf_field_width(t_input *input, t_flags *flags)
{
	int		width;
	char	*ptr;

	width = ft_strtol(input->format + input->index, &ptr, 10);
	return (0);
}

int		get_id(char c)
{
	static char *flags = "-0";
	static char *field_width = "123456788*"; // *
	static char *precision = "."; // * denotes next arg provides num
	static char *length_modifier = "";
	static char	*specifiers = "cspdiuxX%";
	size_t	i;

	i = -1;
	while (c != specifiers[i])
		i++;
	return (i);
}

size_t	parse_format(t_input *input)
{
	t_flags		flags;
	typedef int (*pfunc)(t_input *, t_flags *);
	static pfunc table[256] = {
		['c'] = ft_va_char,
		['s'] = ft_va_string,
		['p'] = ft_va_pointer,
		['d'] = ft_va_integer,
		['i'] = ft_va_integer,
		['u'] = ft_va_ull,
		['x'] = ft_va_hex,
		['X'] = ft_va_hex,
		['%'] = ft_va_percent,
		['-'] = pf_left_adjust,
		['0'] = pf_zero_pad,
		['1'] = pf_field_width,
		['2'] = pf_field_width,
		['3'] = pf_field_width,
		['4'] = pf_field_width,
		['5'] = pf_field_width,
		['6'] = pf_field_width,
		['7'] = pf_field_width,
		['8'] = pf_field_width,
		['9'] = pf_field_width,
		['.'] = pf_precision,
	};
	int		id;

	flags = (t_flags){0};
	id = -1;
	while (input->format[input->index]
		&& !(id = get_id(input)))
	{
		flags.conversion_specifier = id;
		input->length += (*table[id])(input, &flags);
		id = -1;
	}
	return (0);
}

int		ft_printf(const char *format, ...)
{
	t_input	input;

	input = (t_input){0};
	va_start(input.ap, format);
	if (format == NULL)
		return (0);
	input.format = format;
	input.index = 0;
	while (input.format[input.index])
	{
		if (input.format[input.index] == '%')
			input.length += parse_format(&input);
		input.index++;
	}
	return (input.length);
}
