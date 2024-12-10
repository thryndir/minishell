/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thryndir <thryndir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:53:23 by lgalloux          #+#    #+#             */
/*   Updated: 2024/10/22 12:51:12 by thryndir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	if (s == NULL)
		return ;
	while (n)
	{
		*(char *)s = '\0';
		s++;
		n--;
	}
}

/*int main() {
	char buffer[20];
	int i = 0;

	// Affichage du contenu du tampon avant d'utiliser bzero
	printf("Contenu du tampon avant bzero : ");
	while (i < 20) {
		printf("%02X ", (unsigned char)buffer[i]);
		i++;
	}
	printf("\n");

	// Utilisation de bzero pour initialiser le tampon avec des zéros
	bzero(buffer, 10);

	i = 0;  // Réinitialisation de l'indice

	// Affichage du contenu du tampon après avoir utilisé bzero
	printf("Contenu du tampon après bzero : ");
	while (i < 20) {
		printf("%02X ", (unsigned char)buffer[i]);
		i++;
	}
	printf("\n");

	return (0);
}*/