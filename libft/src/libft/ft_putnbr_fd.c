/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:28:21 by lgalloux          #+#    #+#             */
/*   Updated: 2023/11/13 15:50:34 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int nb, int fd)
{
	long	l_nb;

	l_nb = nb;
	if (l_nb < 0)
	{
		l_nb = l_nb * -1;
		write(fd, "-", 1);
	}
	if (l_nb > 9)
		ft_putnbr_fd(l_nb / 10, fd);
	write(fd, &(char){l_nb % 10 + '0'}, 1);
}

/*int main()
{
	ft_putnbr_fd(-2147483648, 1);
}*/