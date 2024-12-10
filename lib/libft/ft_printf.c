/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitelka <aaitelka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:40:29 by aaitelka          #+#    #+#             */
/*   Updated: 2024/11/08 18:53:38 by aaitelka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_hex(va_list ap, char placeholder, int fd)
{
	int	counter;

	counter = 0;
	counter += put_str("0x", fd);
	counter += put_hex(va_arg(ap, unsigned long), placeholder, fd);
	return (counter);
}

static int	check_format(va_list ap, const char *format, int counter, int fd)
{
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (*format == '%' && format++)
				counter += put_char('%', fd);
			else if (*format == 'c' && format++)
				counter += put_char(va_arg(ap, int), fd);
			else if (*format == 's' && format++)
				counter += put_str(va_arg(ap, char *), fd);
			else if ((*format == 'd' || *format == 'i') && format++)
				counter += put_nbr(va_arg(ap, int), fd);
			else if (*format == 'u' && format++)
				counter += put_nbr(va_arg(ap, unsigned int), fd);
			else if (*format == 'x' || *format == 'X')
				counter += put_hex(va_arg(ap, unsigned int), *format++, fd);
			else if (*format == 'p' && *format++)
				counter += check_hex(ap, 'x', fd);
		}
		else
			counter += put_char(*format++, fd);
	}
	return (counter);
}

int	ft_printf(const char *format, ...)
{
	int		printed_count;
	va_list	args;

	printed_count = 0;
	if (write(1, "", 0) == -1)
		return (-1);
	va_start(args, format);
	printed_count = check_format(args, format, printed_count, STDOUT_FILENO);
	va_end(args);
	return (printed_count);
}

int	ft_dprintf(int fd, const char *format, ...)
{
	int		printed_count;
	va_list	args;

	printed_count = 0;
	if (write(1, "", 0) == -1)
		return (-1);
	va_start(args, format);
	printed_count = check_format(args, format, printed_count, fd);
	va_end(args);
	return (printed_count);
}
