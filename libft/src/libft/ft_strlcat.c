/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 13:19:43 by lgalloux          #+#    #+#             */
/*   Updated: 2024/05/29 23:38:02 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	destlen;
	size_t	srclen;
	size_t	space_left;
	size_t	i;

	if (dst == NULL || src == NULL)
		return (0);
	destlen = ft_strlen(dst);
	srclen = ft_strlen((const char *)src);
	if (size <= destlen)
		return (size + srclen);
	space_left = size - destlen - 1;
	i = 0;
	while (src[i] != '\0' && i < space_left)
	{
		dst[destlen + i] = src[i];
		i++;
	}
	dst[destlen + i] = '\0';
	return (destlen + srclen);
}

/*int	main(void)
{
	char source[30] = "les macaques du Congo";
	char destination[40] = "les colibris et ";
	char dest[15];
	//ft_strlcat(destination, source, 40);
	memset(dest, 'r', 15);
	printf("%ld\n", ft_strlcat(dest, "lorem ipsum dolor sit amet", 5));
	printf("%s\n", dest);

	//printf("%s\n", destination);
}*/