/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:17:24 by lgalloux          #+#    #+#             */
/*   Updated: 2024/05/29 23:40:46 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *str, unsigned int start, size_t sublen)
{
	size_t		j;
	size_t		size;
	char		*substr;

	j = 0;
	size = 0;
	if (str == NULL)
		return (NULL);
	if (start >= ft_strlen(str))
		return (ft_strdup(""));
	while (str[start + size])
		size++;
	if (size > sublen)
		size = sublen;
	substr = gc_malloc((size + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	while (j < size && str[start])
		substr[j++] = str[start++];
	substr[j] = '\0';
	return (substr);
}

/*int	main(void)
{
	char *str = "Je test du code";
	printf("%s\n", ft_substr(str, 3, 6));
	return (0);
}*/