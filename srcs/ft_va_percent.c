#include "libft.h"
#include "ft_printf.h"

int		ft_va_percent(t_input *input, t_flags *flags)
{
	(void)input;
	flags->field_width = 0;
	flags->output = ft_strdup("%");
	return (1);
}
