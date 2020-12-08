/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 00:55:03 by jtong             #+#    #+#             */
/*   Updated: 2020/12/01 12:53:32 by jtong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <stdarg.h>
# include "libft.h"

typedef struct	s_input
{
	va_list		ap;
	const char	*format;
	size_t		index;
	size_t		length;
	int			fd;
}				t_input;

typedef struct	s_flags
{
	int		alternate;
	int		zero_pad;
	int		left_adjust;
	int		sign_space;
	int		sign_always;
	int		field_width;
	int		precision;
	int		length_modifier;
	char	conversion_specifier;
	int		base;
	int		capital;
}				t_flags;

int				ft_printf(const char *string, ...);
#endif