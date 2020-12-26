/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 16:01:28 by jtong             #+#    #+#             */
/*   Updated: 2018/11/09 16:26:13 by jtong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strncpy(char *s1, const char *s2, size_t len)
{
	char	*o;
	size_t	i;

	o = s1;
	i = 0;
	if (len == 0)
		return (s1);
	while ((o[i] = s2[i]) && ++i < len)
		;
	while (i < len)
	{
		o[i] = '\0';
		i++;
	}
	return (s1);
}