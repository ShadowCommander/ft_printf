/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pi <pi@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 00:55:03 by jtong             #+#    #+#             */
/*   Updated: 2020/12/09 10:32:02 by pi               ###   ########.fr       */
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
	char	*output;
	int		outputlen;
	char	*prefix;
	int		prefixlen;

	int		alternate;
	int		zero_pad;
	int		left_adjust;
	int		sign_space;
	int		sign_always;
	int		capital;

	int		field_width;
	int		precision;
	int		length_modifier;
	char	conversion_specifier;
	int		base;
}				t_flags;

int				ft_printf(const char *string, ...);
#endif
