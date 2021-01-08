/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 00:54:15 by jtong             #+#    #+#             */
/*   Updated: 2021/01/08 10:43:27 by jtong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int		get_id(char c)
{
	static char	*specifiers = "cspdiuxX%-0.*123456789 ";
	int			i;

	i = 0;
	while (specifiers[i] && c != specifiers[i])
		i++;
	if (!specifiers[i])
		return (-1);
	return (i);
}

int		parse_format(t_input *input)
{
	t_flags		flags;
	static int	(*table[256])(t_input *, t_flags *) = {
		ft_va_char, ft_va_string, ft_va_pointer, ft_va_integer, ft_va_integer,
		ft_va_ull, ft_va_hex, ft_va_hex, ft_va_percent, pf_left_adjust,
		pf_field_width, pf_precision, pf_field_width, pf_field_width,
		pf_field_width, pf_field_width, pf_field_width, pf_field_width,
		pf_field_width, pf_field_width, pf_field_width, pf_field_width, pf_null
	};
	int			id;
	int			ret;

	flags = (t_flags){0, NULL, 0, "\0\0", 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0};
	id = -1;
	while (input->format[input->index]
		&& (id = get_id(input->format[input->index])) != -1)
	{
		flags.conversion_specifier = input->format[input->index];
		if ((ret = (*table[id])(input, &flags)))
		{
			input->index++;
			break ;
		}
		if (ret == -1)
			flags.error = 1;
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

int		ft_vdprintf(int fd, const char *format, va_list ap)
{
	t_input	input;
	int		start;

	va_copy(input.ap, ap);
	input.format = format;
	input.index = 0;
	input.length = 0;
	input.fd = fd;
	if (format == NULL)
		return (0);
	while (input.format[input.index])
	{
		start = input.index;
		while (input.format[input.index] && input.format[input.index] != '%')
			input.index++;
		input.length +=
				write(input.fd, input.format + start, input.index - start);
		if (input.format[input.index] == '%')
		{
			input.index++;
			parse_format(&input);
		}
	}
	return (input.length);
}

int		ft_printf(const char *format, ...)
{
	va_list	ap;
	int		ret;

	va_start(ap, format);
	ret = ft_vdprintf(1, format, ap);
	va_end(ap);
	return (ret);
}