/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 14:06:35 by lgalloux          #+#    #+#             */
/*   Updated: 2024/02/15 18:28:54 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_backcat(char *dst, const char *src, size_t size)
{
	size_t	destlen;
	size_t	srclen;
	size_t	space_left;
	size_t	i;

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
		if (src[i - 1] == '\n')
			break ;
	}
	dst[destlen + i] = '\0';
	return (destlen + srclen);
}

char	*ft_backjoin(const char *str1, const char *str2)
{
	char	*result;
	int		strs_len;
	int		str1_len;
	int		str2_len;

	str1_len = ft_strlen(str1);
	str2_len = ft_strlen(str2);
	strs_len = str1_len + str2_len;
	result = malloc((strs_len + 1));
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, str1, str1_len + 1);
	ft_backcat(result, str2, strs_len + 1);
	free((void *)str1);
	return (result);
}
