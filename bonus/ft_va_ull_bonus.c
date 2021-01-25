/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_va_ull_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 10:41:09 by jtong             #+#    #+#             */
/*   Updated: 2021/01/25 02:33:55 by jtong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf_bonus.h"

static void	ft_va_ull_hlpr(t_flags *flags, unsigned long long num)
{
	flags->umax = num;
	flags->output = ft_ulltoa_base(num, flags->base);
}

int			ft_va_ull(t_input *input, t_flags *flags)
{
	int					len;

	if (flags->base == 0)
		flags->base = 10;
	if (flags->length_modifier == 8 || flags->conversion_specifier == 'p')
		ft_va_ull_hlpr(flags, va_arg(input->ap, unsigned long long));
	else if (flags->length_modifier == 4)
		ft_va_ull_hlpr(flags, va_arg(input->ap, unsigned long));
	else if (flags->length_modifier == 2)
		ft_va_ull_hlpr(flags, (unsigned short)va_arg(input->ap, unsigned int));
	else if (flags->length_modifier == 1)
		ft_va_ull_hlpr(flags, (unsigned char)va_arg(input->ap, unsigned int));
	else
		ft_va_ull_hlpr(flags, va_arg(input->ap, unsigned int));
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
