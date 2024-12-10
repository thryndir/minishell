/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:53:57 by lgalloux          #+#    #+#             */
/*   Updated: 2023/11/16 17:53:16 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *destination, const void *source, size_t size)
{
	unsigned char	*destination2;
	unsigned char	*source2;
	size_t			i;

	destination2 = (unsigned char *)destination;
	source2 = (unsigned char *)source;
	i = -1;
	if (!destination && !source)
		return (0);
	else if (destination > source)
	{
		i += size;
		while (size > 0)
		{
			destination2[i] = source2[i];
			i--;
			size--;
		}
	}
	else
		while (++i < size)
			destination2[i] = source2[i];
	return (destination);
}

/*int main()
{
	char test1[20] = "123456";
	ft_memmove(test1, test1, 6);
	printf("%s\n", test1);

	char test2[20] = "123456";
	ft_memcpy(test2 + 1, test2, 6);
	printf("%s\n", test2)

	char test3[20] = "123456";
	memmove(test3, test3, 6);
	printf("%s\n", test3);

	char test4[20] = "123456";
	memcpy(test4 + 1, test4, 6);
	printf("%s\n", test4);

	return (0);
}*/