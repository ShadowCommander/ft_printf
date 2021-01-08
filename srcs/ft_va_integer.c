#include "libft.h"
#include "ft_printf.h"

int		ft_va_integer(t_input *input, t_flags *flags)
{
	int		num;

	flags->base = 10;
	num = va_arg(input->ap, typeof(num));
	flags->umax = num;
	if (num < 0)
	{
		flags->sign = '-';
		num = -num;
	}
	flags->output = ft_itoa(num);
	return (1);
}
