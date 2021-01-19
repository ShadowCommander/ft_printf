/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 00:54:15 by jtong             #+#    #+#             */
/*   Updated: 2021/01/19 10:14:04 by jtong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int		get_id(char c)
{
	static char	*specifiers = "cspdiuxX%-0.*123456789";
	int			i;

	i = 0;
	while (specifiers[i] && c != specifiers[i])
		i++;
	if (!specifiers[i])
		return (-1);
	return (i);
}

int		(*get_table(int c))(t_input *, t_flags *)
{
	static int	(*table[256])(t_input *, t_flags *) = { ft_va_char,
		ft_va_string, ft_va_pointer, ft_va_integer, ft_va_integer,
		ft_va_ull, ft_va_hex, ft_va_hex, ft_va_percent, pf_left_adjust,
		pf_field_width, pf_precision, pf_field_width, pf_field_width,
		pf_field_width, pf_field_width, pf_field_width, pf_field_width,
		pf_field_width, pf_field_width, pf_field_width, pf_field_width
	};

	if (c < 0 || c > 256)
		return (0);
	return (*table[c]);
}

void	parse_format(t_input *input)
{
	t_flags		flags;
	int			id;
	int			ret;

	flags = (t_flags){0, NULL, 0, "\0\0", 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0};
	id = -1;
	while (input->format[input->index]
		&& (id = get_id(input->format[input->index])) != -1)
	{
		flags.conversion_specifier = input->format[input->index];
		ret = (*get_table(id))(input, &flags);
		input->index++;
		if (ret != 0)
			break ;
		if (ret == -1)
			flags.error = 1;
		id = -1;
	}
	if (id == -1)
		free(flags.output);
	print(input, &flags);
}

int		ft_printf(const char *format, ...)
{
	t_input	input;
	int		start;

	va_start(input.ap, format);
	input.format = format;
	input.index = 0;
	input.length = 0;
	input.fd = 1;
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
	va_end(input.ap);
	return (input.length);
}
