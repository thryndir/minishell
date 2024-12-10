/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:51:49 by lgalloux          #+#    #+#             */
/*   Updated: 2023/10/24 15:51:50 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int test)
{
	if (test >= 0 && test <= 127)
		return (1);
	return (0);
}

/*int main(void)
{
	int test = 128;
	printf("%d\n%d\n", isascii(test), ft_isascii(test));
}*/