/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pi <pi@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 00:55:03 by jtong             #+#    #+#             */
/*   Updated: 2020/12/13 19:01:39 by pi               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <stdarg.h>
# include "libft.h"

/* static char	*specifiers = "cspdiuxX%-0.*123456789"; */

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
	char				conversion_specifier;
	char				*output;
	int					outputlen;
	char				prefix[2];
	char				sign;

	int					alternate;
	int					zero_pad;
	int					left_adjust;

	int					field_width;
	int					precision;
	int					length_modifier;
	int					base;
	int					error;
	int					realsize;
	unsigned long long	umax;
}				t_flags;

int				ft_printf(const char *string, ...);
int				ft_vdprintf(int fd, const char *format, va_list ap);
#endif
