#include "libft.h"
#include "ft_printf.h"

int		ft_va_char(t_input *input, t_flags *flags)
{
	char	c;

	(void)flags;
	c = va_arg(input->ap, int);
	flags->output = ft_strsub(&c, 0, 1);
	return (1);
}
