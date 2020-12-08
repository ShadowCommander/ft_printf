#include "ft_printf.h"

int		ft_va_hex(t_input *input, t_flags *flags)
{
	if (flags->conversion_specifier == 7)
		flags->capital = 1;
	flags->base = 16;
	if (flags->alternate)
	{
		if (flags->capital)
			input->length += write(0, "0X", 2);
		else
			input->length += write(0, "0x", 2);
	}
	ft_va_ull(input, flags);
	return (1);
}