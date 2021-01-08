#include "libft.h"
#include "ft_printf.h"

int		verify(t_input *input, t_flags *flags)
{
	(void)input;
	if (flags->output == NULL)
	{
		if (flags->conversion_specifier == 's')
		{
			if (flags->precision < 0 || flags->precision >= 6)
				flags->output = ft_strdup("(null)");
			else
				flags->output = ft_strdup("");
		}
		else
			return (0);
	}
	if (flags->conversion_specifier == 's')
	{
		flags->zero_pad = 0;
		flags->precision = -1;
	}
	return (1);
}

void	get_size(t_input *input, t_flags *flags)
{
	(void)input;
	if (flags->conversion_specifier == 'c')
		flags->outputlen = 1;
	else if (flags->output)
		flags->outputlen = ft_strlen(flags->output);
	if (flags->umax == 0 && flags->precision == 0)
		flags->outputlen = 0;
	flags->realsize = flags->outputlen;
	if (flags->precision > flags->outputlen)
		flags->realsize = flags->precision;
	if (flags->precision >= 0)
		flags->zero_pad = 0;
	if (flags->sign)
		flags->realsize++;
	if (flags->prefix[1])
	{
		flags->prefix[0] = '0';
		flags->realsize += 2;
	}
}

void	pad(t_input *input, int len, char c)
{
	if (len <= 0)
		return ;
	input->length += len;
	while (len-- > 0)
		write(1, &c, 1);
}

void	print(t_input *input, t_flags *flags)
{
	if (!verify(input, flags))
		return ;
	get_size(input, flags);
	if (!flags->left_adjust && !flags->zero_pad)
		pad(input, flags->field_width - flags->realsize, ' ');
	if (flags->sign)
		input->length += write(1, &flags->sign, 1);
	if (flags->prefix[0])
		input->length += write(input->fd, flags->prefix, 2);
	if (!flags->left_adjust && flags->zero_pad)
		pad(input, flags->field_width - flags->realsize, '0');
	pad(input, flags->precision - flags->outputlen, '0');
	input->length += write(input->fd, flags->output, flags->outputlen);
	free(flags->output);
	if (flags->left_adjust)
		pad(input, flags->field_width - flags->realsize, ' ');
}
