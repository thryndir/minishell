/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 15:33:42 by lgalloux          #+#    #+#             */
/*   Updated: 2024/09/11 17:31:34 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_which_type(char type, int fd, va_list l_arg)
{
	if (type == 'c')
		return (ft_printchar(va_arg(l_arg, int), fd));
	else if (type == 's')
		return (ft_printstr(va_arg(l_arg, char *), fd));
	else if (type == 'p')
		return (ft_printptr(va_arg(l_arg, void *), fd));
	else if (type == 'd' || type == 'i')
		return (ft_printnbr(va_arg(l_arg, int), fd));
	else if (type == 'u')
		return (ft_printunbr_base(va_arg(l_arg, unsigned int),
				fd, "0123456789"));
	else if (type == 'x')
		return (ft_printunbr_base(va_arg(l_arg, unsigned int), fd, MIN));
	else if (type == 'X')
		return (ft_printunbr_base(va_arg(l_arg, unsigned int), fd, MAJ));
	else if (type == '%')
		return (ft_printchar('%', fd));
	return (0);
}

int	exec(int fd, const char *format, va_list l_arg)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			len += ft_which_type(format[i + 1], fd, l_arg);
			i += 2;
		}
		else
		{
			write(fd, &format[i++], 1);
			len++;
		}
	}
	return (len);
}

int	ft_dprintf(int fd, const char *format, ...)
{
	va_list	l_arg;

	va_start(l_arg, format);
	return (exec(fd, format, l_arg));
}

int	ft_printf(const char *format, ...)
{
	va_list	l_arg;

	va_start(l_arg, format);
	return (exec(1, format, l_arg));
}

// int	main(void)
// {
// 	printf(" -> %d\n",ft_printf(" NULL %s NULL ", "test"));
// 	printf("-----------------\n");
// 	printf(" -> %d\n", printf("NULL %s NULL ", "test"));
// }