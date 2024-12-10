/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:53:08 by lgalloux          #+#    #+#             */
/*   Updated: 2024/05/29 23:44:29 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int x, size_t n)
{
	unsigned char	*p;

	p = ptr;
	if (ptr == NULL)
		return (NULL);
	while (n != 0)
	{
		*p = (unsigned char)x;
		p++;
		n--;
	}
	return (ptr);
}

/*int main() {
	char buffer[20];
	char buffer2[20];

	// Utilisation de memset pour remplir le tableau de 'A's
	ft_memset(buffer2, 'A', 15);
	memset(buffer, 'A', 15);

	// Affichage du contenu du tableau
	printf("Contenu du tableau après memset : %s\n", buffer2);
	printf("Contenu du tableau après memset : %s\n", buffer);

	return (0);
}*/