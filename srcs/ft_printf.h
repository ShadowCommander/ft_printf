/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 00:55:03 by jtong             #+#    #+#             */
/*   Updated: 2021/01/08 14:49:44 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
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
int				ft_va_string(t_input *input, t_flags *flags);
int				ft_va_char(t_input *input, t_flags *flags);
int				ft_va_ull(t_input *input, t_flags *flags);
int				ft_va_integer(t_input *input, t_flags *flags);
int				ft_va_hex(t_input *input, t_flags *flags);
int				ft_va_pointer(t_input *input, t_flags *flags);
int				ft_va_percent(t_input *input, t_flags *flags);
int				pf_left_adjust(t_input *input, t_flags *flags);
int				pf_zero_pad(t_input *input, t_flags *flags);
int				pf_field_width(t_input *input, t_flags *flags);
int				pf_precision(t_input *input, t_flags *flags);
int				pf_null(t_input *input, t_flags *flags);
int				pf_space(t_input *input, t_flags *flags);
int				verify(t_input *input, t_flags *flags);
void			get_size(t_input *input, t_flags *flags);
void			pad(t_input *input, int len, char c);
void			print(t_input *input, t_flags *flags);
#endif
