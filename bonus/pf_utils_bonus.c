/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_utils_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 10:41:11 by jtong             #+#    #+#             */
/*   Updated: 2021/01/19 11:45:54 by jtong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf_bonus.h"

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
		flags->field_width =
			(int)ft_strtol(input->format + input->index, &ptr, 10);
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
		flags->precision =
			(int)ft_strtol(input->format + input->index, &ptr, 10);
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
