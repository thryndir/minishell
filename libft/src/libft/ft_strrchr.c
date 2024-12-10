/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:21:04 by lgalloux          #+#    #+#             */
/*   Updated: 2024/05/29 23:39:54 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *string, int searchedChar)
{
	int	cpt;

	cpt = 0;
	if (string == NULL)
		return (NULL);
	while (*string != '\0')
	{
		string++;
		cpt++;
	}
	while (cpt != 0)
	{
		if (*string == (unsigned char)searchedChar)
			return ((char *)string);
		string--;
		cpt--;
	}
	if (*string == (const char)searchedChar)
		return ((char *)string);
	return (NULL);
}

/*int	main(void)
{
	char *string = "La string de test";
	int searchedChar = 'd';
	printf("%s\n", ft_strrchr(string, searchedChar));
	printf("%s\n", strrchr(string, searchedChar));
}*/