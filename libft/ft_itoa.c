/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itao.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 22:36:57 by jtong             #+#    #+#             */
/*   Updated: 2018/11/12 15:35:30 by jtong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_itoa(int n)
{
	int		cpy;
	int		size;
	int		neg;
	char	*str;

	cpy = n;
	size = cpy ? 0 : 1;
	while (cpy != 0)
	{
		cpy /= 10;
		size++;
	}
	neg = n < 0 ? 1 : 0;
	if (!(str = (char *)malloc(sizeof(*str) * (size + 1 + neg))))
		return (NULL);
	str[size + neg] = '\0';
	if (neg)
		str[0] = '-';
	while (size-- > 0)
	{
		str[size + neg] = ((neg ? -1 : 1) * (n % 10)) + '0';
		n /= 10;
	}
	return (str);
}
