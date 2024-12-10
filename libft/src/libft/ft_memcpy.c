/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:53:39 by lgalloux          #+#    #+#             */
/*   Updated: 2023/11/16 16:33:07 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *destination, const void *source, size_t size)
{
	unsigned char	*destination2;
	unsigned char	*source2;
	size_t			i;

	destination2 = (unsigned char *)destination;
	source2 = (unsigned char *)source;
	i = 0;
	if (destination == NULL && source == NULL)
		return (0);
	while (i < size)
	{
		destination2[i] = source2[i];
		i++;
	}
	return (destination);
}

/*int main() {
	char source[] = "Ceci est un exemple.";
	char destination[30];
	ft_memcpy(destination, source, strlen(source) + 1);
	printf("Tableau de destination : %s\n", destination);
	return (0);
}*/