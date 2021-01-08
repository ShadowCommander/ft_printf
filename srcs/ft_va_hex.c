#include "libft.h"
#include "ft_printf.h"

int		ft_va_hex(t_input *input, t_flags *flags)
{
	flags->base = 16;
	ft_va_ull(input, flags);
	if (flags->alternate && flags->umax != 0)
		flags->prefix[1] = flags->conversion_specifier;
	return (1);
}
