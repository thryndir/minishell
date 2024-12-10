/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:20:54 by lgalloux          #+#    #+#             */
/*   Updated: 2024/05/27 22:20:11 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *first, const char *second, size_t length)
{
	size_t	i;

	i = 0;
	if (first == NULL || second == NULL)
		return (0);
	if (length == 0)
		return (0);
	while (first[i] == second[i] && first[i] != '\0')
	{
		if (i < (length - 1))
			i++;
		else
			return (0);
	}
	return ((unsigned char)(first[i]) - (unsigned char)(second[i]));
}

/*int main(void)
{
	char *first = "\x12\xff\x65\x12\xbd\xde\xad";
	char *second = "\x12\x02";
	size_t length = 6;
	printf("%d\n",ft_strncmp(first, second, length));
	printf("%d\n",strncmp(first, second, length));
}*/