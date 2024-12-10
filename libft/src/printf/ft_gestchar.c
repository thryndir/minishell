/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gestchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:35:47 by lgalloux          #+#    #+#             */
/*   Updated: 2024/05/11 23:34:16 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printchar(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

int	ft_printstr(char *str, int fd)
{
	int	i;

	i = 0;
	if (!str)
	{
		ft_printstr("(null)", fd);
		return (6);
	}
	while (str[i])
		write(fd, &str[i++], 1);
	return (i);
}
