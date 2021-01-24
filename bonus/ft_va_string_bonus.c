/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_va_string_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 00:54:15 by jtong             #+#    #+#             */
/*   Updated: 2021/01/19 13:06:02 by jtong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"
#include "libft.h"

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
	flags->sign = '\0';
	return (1);
}
