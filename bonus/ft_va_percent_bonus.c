/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_va_percent_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 10:41:03 by jtong             #+#    #+#             */
/*   Updated: 2021/01/19 11:45:38 by jtong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf_bonus.h"

int		ft_va_percent(t_input *input, t_flags *flags)
{
	(void)input;
	flags->field_width = 0;
	flags->output = ft_strdup("%");
	return (1);
}
