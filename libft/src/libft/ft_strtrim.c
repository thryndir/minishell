/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 15:06:40 by lgalloux          #+#    #+#             */
/*   Updated: 2024/05/27 21:36:12 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *str, const char *set)
{
	int		start;
	int		size;

	if (!str || !set)
		return (NULL);
	start = 0;
	while (str[start] && ft_strchr(set, str[start]))
		start++;
	size = ft_strlen(str) - 1;
	while (size > start && ft_strchr(set, str[size]))
		size--;
	size -= start - 1;
	return (ft_substr(str, start, size));
}
