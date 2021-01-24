/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_va_printed_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 11:37:57 by jtong             #+#    #+#             */
/*   Updated: 2021/01/19 11:45:43 by jtong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf_bonus.h"

int		ft_va_printed(t_input *input, t_flags *flags)
{
	int		*n;

	(void)flags;
	n = va_arg(input->ap, typeof(n));
	*n = input->length;
	return (1);
}
