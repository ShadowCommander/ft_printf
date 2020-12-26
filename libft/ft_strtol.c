/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pi <pi@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 14:12:37 by jtong             #+#    #+#             */
/*   Updated: 2020/12/10 21:27:34 by pi               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <limits.h>

static int		ft_ctoi(int c)
{
	if (ft_isdigit(c))
		return (c - '0');
	else if (ft_isupper(c))
		return (c - ('A' - 10));
	else if (ft_islower(c))
		return (c - ('a' - 10));
	return (c);
}

long			ft_strtol(const char *ptr, char **endptr, int base)
{
	t_strtol	vars;

	if (base <= 1 || base > 16)
		return (0);
	vars.neg = 1;
	vars.s = ptr;
	while (ft_isspace(*vars.s))
		vars.s++;
	if ((*vars.s == '-' || *vars.s == '+') && ft_isalnum(vars.s[1]))
		vars.neg = *vars.s++ == '-' ? -1 : 1;
	vars.cutoff = (LONG_MAX * vars.neg) / base;
	vars.cutlim = (LONG_MAX * vars.neg) % base;
	vars.acc = 0;
	while (ft_isalnum(*vars.s) && (vars.c = ft_ctoi(*vars.s)) < base)
	{
		if (vars.acc >= vars.cutoff * vars.neg &&
				vars.c > vars.cutlim + (vars.neg == -1))
			return (LONG_MAX * vars.neg);
		vars.acc = (vars.acc * base) + (vars.c * vars.neg);
		vars.s++;
	}
	if (endptr)
		*endptr = (char *)(vars.s);
	return (vars.acc);
}
