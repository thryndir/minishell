/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:52:10 by lgalloux          #+#    #+#             */
/*   Updated: 2023/10/24 15:52:11 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int test)
{
	if (test >= 32 && test <= 126)
		return (1);
	return (0);
}

/*int main(void)
{
	int test = 127;
	printf("%d\n%d\n", isprint(test), ft_isprint(test));
}*/