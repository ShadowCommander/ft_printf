/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_va_integer_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 10:41:01 by jtong             #+#    #+#             */
/*   Updated: 2021/01/19 13:13:20 by jtong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf_bonus.h"

int		ft_va_integer(t_input *input, t_flags *flags)
{
	flags->base = 10;
	if (flags->length_modifier == 8 || flags->conversion_specifier == 'p')
		flags->umax = va_arg(input->ap, long long);
	else if (flags->length_modifier == 4)
		flags->umax = va_arg(input->ap, long);
	else if (flags->length_modifier == 2)
		flags->umax = (short)va_arg(input->ap, int);
	else if (flags->length_modifier == 1)
		flags->umax = (char)va_arg(input->ap, int);
	else
		flags->umax = va_arg(input->ap, int);
	if ((long long)flags->umax < 0)
	{
		flags->sign = '-';
		flags->umax = -flags->umax;
	}
	flags->output = ft_lltoa(flags->umax);
	return (1);
}
