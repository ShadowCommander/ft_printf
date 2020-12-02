/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ulltoa_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 20:28:35 by jtong             #+#    #+#             */
/*   Updated: 2019/05/30 14:51:39 by jtong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static char	ft_getdigit(int i)
{
	if (i >= 0 && i <= 35)
		return ("0123456789abcdefghijklmnopqrstuvwxyz"[i]);
	return ('\0');
}

char		*ft_ulltoa_base(unsigned long long n, int base)
{
	unsigned long long	cpy;
	size_t				size;
	char				*str;

	if (base < 2 || base > 35)
		return (NULL);
	cpy = n;
	size = n ? 0 : 1;
	if (cpy != 0)
		while (++size && (cpy /= base) != 0)
			;
	if (!(str = ft_strnew(size)))
		return (NULL);
	while (size-- > 0)
	{
		str[size] = ft_getdigit(n % base);
		n /= base;
	}
	return (str);
}
