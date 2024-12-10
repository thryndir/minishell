/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gesthexa.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:51:01 by lgalloux          #+#    #+#             */
/*   Updated: 2024/05/11 23:38:33 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printptr(void *address, int fd)
{
	unsigned long long int	addr;
	char					addr_str[16];
	int						len;
	int						i;

	addr = (unsigned long long int)address;
	len = 0;
	if (address == NULL)
	{
		ft_printstr("(nil)", fd);
		return (5);
	}
	while (addr > 0)
	{
		addr_str[len++] = "0123456789abcdef"[addr % 16];
		addr /= 16;
	}
	i = len - 1;
	ft_printstr("0x", fd);
	while (i >= 0)
		ft_printchar(addr_str[i--], fd);
	return (len + 2);
}

int	ft_printnbr_base(int nb, int fd, char *base)
{
	long		l_nb;
	int			cpt_nbr;
	int			minus;
	int			len;

	l_nb = nb;
	cpt_nbr = 1;
	minus = 0;
	len = ft_strlen(base);
	if (l_nb < 0)
	{
		l_nb = l_nb * -1;
		minus = 1;
		cpt_nbr++;
	}
	if (l_nb > len)
	{
		cpt_nbr = ft_printnbr_base(l_nb / len, fd, base) + 1 + minus;
	}
	write(fd, &(char){base[l_nb % len]}, 1);
	return (cpt_nbr);
}
