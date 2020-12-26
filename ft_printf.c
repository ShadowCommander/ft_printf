/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pi <pi@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 00:54:15 by jtong             #+#    #+#             */
/*   Updated: 2020/12/26 23:15:08 by pi               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include "ft_printf.h"
#include "libft.h"

char	*ft_itoa(int n)
{
	int		cpy;
	int		size;
	char	*str;

	cpy = n;
	size = cpy ? 0 : 1;
	while (cpy != 0)
	{
		cpy /= 10;
		size++;
	}
	if (!(str = (char *)malloc(sizeof(*str) * (size + 1))))
		return (NULL);
	str[size] = '\0';
	while (size-- > 0)
	{
		str[size] = ((n < 0 ? -1 : 1) * (n % 10)) + '0';
		n /= 10;
	}
	return (str);
}


int		ft_va_integer(t_input *input, t_flags *flags)
{
	int		num;

	flags->base = 10;
	num = va_arg(input->ap, typeof(num));
	flags->umax = num;
	if (num < 0)
	{
		flags->sign = '-';
		num = -num;
	}
	flags->output = ft_itoa(num);
	return (1);
}

int		ft_va_string(t_input *input, t_flags *flags)
{
	char	*str;

	str = va_arg(input->ap, typeof(str));
	if (str == NULL)
	{
		flags->output = NULL;
		return (1);
	}
	if (flags->precision == -1)
		flags->output = ft_strdup(str);
	else
		flags->output = ft_strsub(str, 0, flags->precision);
	flags->precision = 0;
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
	int					len;

	if (flags->base == 0)
		flags->base = 10;
	if (flags->length_modifier == 1 || flags->conversion_specifier == 'p')
		flags->umax = va_arg(input->ap, unsigned long long);
	else if (flags->length_modifier == 1)
		flags->umax = va_arg(input->ap, unsigned long);
	else
		flags->umax = va_arg(input->ap, unsigned int);
	flags->output = ft_ulltoa_base(flags->umax, flags->base);
	if (flags->conversion_specifier == 'X')
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
	flags->base = 16;
	ft_va_ull(input, flags);
	if (flags->alternate && flags->umax != 0)
		flags->prefix[1] = flags->conversion_specifier;
	return (1);
}

int		ft_va_pointer(t_input *input, t_flags *flags)
{
	void	*ptr;

	flags->base = 16;
	ptr = va_arg(input->ap, typeof(ptr));
	if (ptr == NULL)
	{
		flags->output = ft_strdup("(nil)");
		flags->precision = -1;
	}
	else
	{
		flags->prefix[1] = 'x';
		flags->output = ft_ulltoa_base((unsigned long long)ptr, flags->base);
	}
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

	if (input->format[input->index] == '0')
		flags->zero_pad = 1;
	// if * then va_arg next arg
	if (input->format[input->index] == '*')
	{
		flags->field_width = va_arg(input->ap, int);
		if (flags->field_width < 0)
		{
			flags->field_width *= -1;
			flags->left_adjust = 1;
		}
	}
	else
	{
		flags->field_width = (int)ft_strtol(input->format + input->index, &ptr, 10);
		input->index = ptr - input->format - 1;
	}
	return (0);
}

int		pf_precision(t_input *input, t_flags *flags)
{
	char	*ptr;

	input->index++;
	flags->precision = 0;
	if (input->format[input->index] == '*')
	{
		flags->precision = va_arg(input->ap, int);
		if (flags->precision < 0)
		{
			flags->precision = -1;
			flags->left_adjust = 1;
		}
	}
	else
	{
		flags->precision = (int)ft_strtol(input->format + input->index, &ptr, 10);
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

int		ft_max(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

int		verify(t_input *input, t_flags *flags)
{
	(void)input;
	if (flags->output == NULL)
	{
		if (flags->conversion_specifier == 's')
		{
			if (flags->precision < 0 || flags->precision >= 6)
			{
				flags->output = ft_strdup("(null)");
				// flags->precision = 0;
			}
			else
				flags->output = ft_strdup("");
		}
		else
			return (0);
	}
	if (flags->conversion_specifier == 's')
	{
		flags->zero_pad = 0;
		flags->precision = -1;
	}
	return (1);
}

void	get_size(t_input *input, t_flags *flags)
{
	(void)input;
	if (flags->conversion_specifier == 'c')
		flags->outputlen = 1;
	else if (flags->output)
		flags->outputlen = ft_strlen(flags->output);
	if (flags->umax == 0 && flags->precision == 0)
		flags->outputlen = 0;
	flags->realsize = flags->outputlen;
	if (flags->precision > flags->outputlen)
		flags->realsize = flags->precision;
	if (flags->precision >= 0)
		flags->zero_pad = 0;
	if (flags->sign)
		flags->realsize++;
	if (flags->prefix[1])
	{
		flags->prefix[0] = '0';
		flags->realsize += 2;
	}
	// padding = flags->field_width - flags->precision - flags->outputlen + flags->prefixlen;
}

void	pad(t_input *input, int len, char c)
{
	if (len <= 0)
		return ;
	input->length += len;
	while (len-- > 0)
		write(1, &c, 1);
}

void	print(t_input *input, t_flags *flags)
{

	if (!verify(input, flags))
		return;
	get_size(input, flags);
	if (!flags->left_adjust && !flags->zero_pad)
		pad(input, flags->field_width - flags->realsize, ' ');
	if (flags->sign)
		input->length += write(1, &flags->sign, 1);
	if (flags->prefix[0])
		input->length += write(input->fd, flags->prefix, 2);
	if (!flags->left_adjust && flags->zero_pad)
		pad(input, flags->field_width - flags->realsize, '0');
	pad(input, flags->precision - flags->outputlen, '0');
	input->length += write(input->fd, flags->output, flags->outputlen);
	free(flags->output);
	if (flags->left_adjust)
		pad(input, flags->field_width - flags->realsize, ' ');
}

/// f_func returns whether to stop parsing
int		parse_format(t_input *input)
{
	t_flags			flags;
	typedef int		(*f_func)(t_input *, t_flags *);
	static f_func	table[256] = {
		ft_va_char, ft_va_string, ft_va_pointer, ft_va_integer, ft_va_integer, ft_va_ull, ft_va_hex, ft_va_hex, ft_va_percent, pf_left_adjust, pf_field_width, pf_precision, pf_field_width, pf_field_width, pf_field_width, pf_field_width, pf_field_width, pf_field_width, pf_field_width, pf_field_width, pf_field_width, pf_field_width,
	};
	int				id;
	int				ret;
	size_t			start;

	start = input->index;
	flags = (t_flags){'\0', NULL, 0, "\0\0", '\0', 0, 0, 0, 0, -1, 0, 0, 0, 0, 0};
	id = -1;
	while (input->format[input->index]
		&& (id = get_id(input->format[input->index])) != -1)
	{
		flags.conversion_specifier = input->format[input->index];
		if ((ret = (*table[id])(input, &flags)))
		{
			input->index++;
			break;
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

	input = (t_input){ap, format, 0, 0, fd};
	if (format == NULL)
		return (0);
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
				;//return (-1);
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
