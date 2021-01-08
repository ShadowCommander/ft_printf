
#include "libft.h"
#include "ft_printf.h"

int		ft_va_ull(t_input *input, t_flags *flags)
{
	int					len;

	if (flags->base == 0)
		flags->base = 10;
	if (flags->length_modifier == 1 || flags->conversion_specifier == 'p')
		flags->umax = va_arg(input->ap, unsigned long long);
	else if (flags->length_modifier == 1)
		flags->umax = va_arg(input->ap, unsigned long);
	else
		flags->umax = va_arg(input->ap, unsigned int);
	flags->output = ft_ulltoa_base(flags->umax, flags->base);
	if (flags->conversion_specifier == 'X')
	{
		len = 0;
		while (flags->output[len])
		{
			flags->output[len] = ft_toupper(flags->output[len]);
			len++;
		}
	}
	return (1);
}
