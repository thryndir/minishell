/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:51:06 by lgalloux          #+#    #+#             */
/*   Updated: 2023/10/24 15:51:08 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int test)
{
	if (test >= '0' && test <= '9')
		return (1);
	return (0);
}

/*int	main(void)
{
	int value = 'a';
	printf("%d\n%d\n", ft_isdigit(value), isdigit(value));
}*/