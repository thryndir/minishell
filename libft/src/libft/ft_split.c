/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 18:16:31 by lgalloux          #+#    #+#             */
/*   Updated: 2024/11/19 21:45:57 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strnbr(const char *str, char c)
{
	int	result;
	int	i;

	result = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i])
			result++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (result);
}

int	ft_charnbr(const char *str, char c)
{
	int	i;
	int	charcount;

	i = 0;
	charcount = 0;
	while (str[i] && str[i] != c)
	{
		charcount++;
		i++;
	}
	return (charcount);
}

void	ft_malloc_fail(char **strs, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		gc_free(strs[i]);
		i++;
	}
	gc_free(strs);
}

char	**ft_str_to_array(char **strs, const char *str, char c)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (j < ft_strnbr(str, c))
	{
		k = 0;
		while (str[i] && str[i] == c)
			i++;
		strs[j] = gc_malloc((ft_charnbr(str + i, c) + 1) * sizeof(char));
		if (strs[j] == NULL)
		{
			ft_malloc_fail(strs, j);
			return (NULL);
		}
		while (str[i] && str[i] != c)
			strs[j][k++] = str[i++];
		strs[j++][k] = '\0';
	}
	strs[j] = NULL;
	return (strs);
}

char	**ft_split(char const *str, char c)
{
	char	**strs;

	if (str == NULL)
		return (NULL);
	strs = (char **)gc_malloc((ft_strnbr(str, c) + 1) * sizeof(char *));
	if (strs == NULL)
		return (NULL);
	strs = ft_str_to_array(strs, str, c);
	return (strs);
}

/*int	main(void)
{
	char *str = "!!!!Les!!bananes!du!!!!!!Guatemala";
	char c = '!';
	int i = 0;
	char **result = ft_split(str, c);
	while(result[i] != NULL)
	{
		printf("%s", result[i]);
		i++;
	}
}*/