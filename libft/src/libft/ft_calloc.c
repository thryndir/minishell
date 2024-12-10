/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thryndir <thryndir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:16:45 by lgalloux          #+#    #+#             */
/*   Updated: 2024/10/18 15:02:01 by thryndir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t elementCount, size_t elementSize)
{
	unsigned char	*memory;
	size_t			i;

	if (!elementCount || !elementSize)
		return (NULL);
	memory = gc_malloc(elementCount * elementSize);
	if (memory == NULL)
		return (NULL);
	i = 0;
	while (i < elementCount * elementSize)
	{
		memory[i] = '\0';
		i++;
	}
	return ((void *)memory);
}

/*int	main(void)
{
	size_t elementCount = 8;
	size_t elementSize = 3;
	printf("%p\n", ft_calloc(elementCount, elementSize));
}*/