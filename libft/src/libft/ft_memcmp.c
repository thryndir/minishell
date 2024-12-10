/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:21:36 by lgalloux          #+#    #+#             */
/*   Updated: 2024/05/29 23:32:30 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *pointer1, const void *pointer2, size_t size)
{
	size_t	i;

	i = 0;
	if (pointer1 == NULL || pointer2 == NULL)
		return (0);
	while (i < size)
	{
		if (*(unsigned char *)pointer1 != *(unsigned char *)pointer2)
			return (*(unsigned char *)pointer1 - *(unsigned char *)pointer2);
		pointer1++;
		pointer2++;
		i++;
	}
	return (0);
}

/*int	main(void)
{
	int array1 [] = { 'a', 'b', 'c', 'd', 'e' };
	int array2 [] = { 'a', 'b', 'c', 'd', 'e' };
	size_t size = 5;
	printf("%d\n", ft_memcmp(array1, array2, size));
	printf("%d\n", memcmp(array1, array2, size));
}*/