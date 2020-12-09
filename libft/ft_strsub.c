/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 18:30:15 by jtong             #+#    #+#             */
/*   Updated: 2018/11/09 16:15:41 by jtong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str;

	if (!s || !(str = (char *)malloc(sizeof(*str) * (len + 1))))
		return (NULL);
	ft_strncpy(str, s + start, len);
	str[len] = '\0';
	return (str);
}
