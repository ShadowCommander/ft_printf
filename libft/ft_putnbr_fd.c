/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtong <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 15:58:55 by jtong             #+#    #+#             */
/*   Updated: 2019/02/25 14:17:43 by jtong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	ft_putnbr_fd(int n, int fd)
{
	ssize_t	size;

	size = 0;
	if (n >= 10 || n <= -10)
		size = ft_putnbr_fd(n / 10, fd);
	else if (n < 0)
		size += ft_putchar_fd('-', fd);
	if (n < 0)
		size += ft_putchar_fd(-(n % 10) + '0', fd);
	else
		size += ft_putchar_fd((n % 10) + '0', fd);
	return (size);
}
