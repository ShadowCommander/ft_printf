/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtong <pi@student.42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 00:54:15 by jtong             #+#    #+#             */
/*   Updated: 2020/12/26 23:15:08 by pi               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
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
	return (1);
}
