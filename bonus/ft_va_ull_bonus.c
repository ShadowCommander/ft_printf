/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_va_ull_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 10:41:09 by jtong             #+#    #+#             */
/*   Updated: 2021/01/19 12:10:38 by jtong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf_bonus.h"

int		ft_va_ull(t_input *input, t_flags *flags)
{
	int					len;

	if (flags->base == 0)
		flags->base = 10;
	if (flags->length_modifier == 8 || flags->conversion_specifier == 'p')
		flags->umax = va_arg(input->ap, unsigned long long);
	else if (flags->length_modifier == 4)
		flags->umax = va_arg(input->ap, unsigned long);
	else if (flags->length_modifier == 2)
		flags->umax = (short)va_arg(input->ap, unsigned int);
	else if (flags->length_modifier == 1)
		flags->umax = (char)va_arg(input->ap, unsigned int);
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

