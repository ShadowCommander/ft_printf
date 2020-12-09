/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 14:16:09 by jtong             #+#    #+#             */
/*   Updated: 2019/05/30 15:16:09 by jtong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strndup(const char *src, size_t len)
{
	char	*dst;

	if (!(dst = (char *)malloc(sizeof(*dst) * (len + 1))))
		return (NULL);
	dst[len] = '\0';
	ft_strncpy(dst, src, len);
	return (dst);
}
