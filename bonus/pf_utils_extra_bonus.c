/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_utils_extra_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 14:46:16 by jtong             #+#    #+#             */
/*   Updated: 2021/01/25 02:33:43 by jtong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int		pf_space(t_input *input, t_flags *flags)
{
	(void)input;
	flags->sign = ' ';
	return (0);
}

int		pf_long(t_input *input, t_flags *flags)
{
	flags->length_modifier = 4;
	if (input->format[input->index + 1] == 'l')
	{
		input->index++;
		flags->length_modifier = 8;
	}
	return (0);
}

int		pf_char(t_input *input, t_flags *flags)
{
	flags->length_modifier = 2;
	if (input->format[input->index + 1] == 'h')
	{
		input->index++;
		flags->length_modifier = 1;
	}
	return (0);
}

int		pf_alternate(t_input *input, t_flags *flags)
{
	(void)input;
	flags->alternate = 1;
	return (0);
}

int		pf_plus(t_input *input, t_flags *flags)
{
	(void)input;
	flags->sign = '+';
	return (0);
}
