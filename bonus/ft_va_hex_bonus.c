/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_va_hex_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 10:40:58 by jtong             #+#    #+#             */
/*   Updated: 2021/01/19 11:45:33 by jtong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf_bonus.h"

int		ft_va_hex(t_input *input, t_flags *flags)
{
	flags->base = 16;
	ft_va_ull(input, flags);
	if (flags->alternate && flags->umax != 0)
		flags->prefix[1] = flags->conversion_specifier;
	return (1);
}
