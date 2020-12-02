/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 23:38:57 by jtong             #+#    #+#             */
/*   Updated: 2019/05/30 14:54:25 by jtong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	unsigned long	output;
**	int				neg;
**	unsigned long	cutoff;
**
**	neg = 0;
**	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\v' ||
**			*str == '\f' || *str == '\r')
**		str++;
**	if (*str == '-' || *str == '+')
**		if (str[1] >= '0' && str[1] <= '9')
**		{
**			neg = (*str == '-') ? 1 : 0;
**			str++;
**		}
**	cutoff = (neg ? LONG_MIN : LONG_MAX) / 10;
**	output = 0;
**	while (*str >= '0' && *str <= '9')
**		if ((neg ? output <= cutoff : output >= cutoff) && *str - '0' > 7 + neg)
**			return ((int)(neg ? LONG_MIN : LONG_MAX));
**		else
**			output = (output * 10) + ((*str++ - '0') * (neg ? -1 : 1));
**	return ((int)output);
*/

int		ft_atoi(const char *str)
{
	return ((int)ft_strtol(str, (char **)NULL, 10));
}
