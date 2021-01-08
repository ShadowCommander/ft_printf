/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_va_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 10:41:04 by jtong             #+#    #+#             */
/*   Updated: 2021/01/08 10:41:19 by jtong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int		ft_va_pointer(t_input *input, t_flags *flags)
{
	void	*ptr;

	flags->base = 16;
	ptr = va_arg(input->ap, typeof(ptr));
	if (ptr == NULL)
	{
		flags->output = ft_strdup("(nil)");
		flags->precision = -1;
	}
	else
	{
		flags->prefix[1] = 'x';
		flags->output = ft_ulltoa_base((unsigned long long)ptr, flags->base);
	}
	return (1);
}
