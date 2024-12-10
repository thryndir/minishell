/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_word_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 23:36:10 by lgalloux          #+#    #+#             */
/*   Updated: 2024/05/27 21:53:23 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_word_in(const char *str, const char *word, int len)
{
	int	i;
	int	j;

	i = 0;
	if (word == NULL)
		return (0);
	while (str[i])
	{
		j = 0;
		while (str[i + j] == word[j] && word[j])
		{
			if (j == len - 1 && (str[i + j + 1] == '\0'
					|| ft_isspace(str[i + j + 1])))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

// int	main(void)
// {
// 	printf("%d", ft_is_word_in("noixdenoixco gga qgqq", "noix", 4));
// 	return (0);
// }
