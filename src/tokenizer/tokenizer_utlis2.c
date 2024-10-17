/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utlis2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgerbaul <jgerbaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 22:51:49 by jgerbaul          #+#    #+#             */
/*   Updated: 2024/10/17 22:05:44 by jgerbaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * Main word counter here, the other two are here because of
 * the 25 line restriction.
*/
int	count_word(const char *str, int *i)
{
	if (is_double_symbol(str, *i))
	{
		*i += 2;
		return (1);
	}
	if (is_symbol(str[*i]) && !is_quote(str[*i]))
	{
		(*i)++;
		return (1);
	}
	if (is_quote(str[*i]))
		return (count_quoted_word(str, i));
	if (str[*i] && !is_symbol(str[*i]) && str[*i] != ' ')
		return (count_regular_word(str, i));
	return (0);
}

/**
 * This function count the number a word in the input string.
*/
int	ft_strnbr(const char *str)
{
	int	result;
	int	i;

	result = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] == ' ')
			i++;
		result += count_word(str, &i);
	}
	return (result);
}

/**
 * This function give back the number of char before specific
 * requirements (quote search).
*/
int	ft_charnbr(const char *str)
{
	int		i;
	char	quote;

	i = 0;
	if (is_double_symbol(str, 0))
		return (2);
	if (is_symbol(str[0]) && !is_quote(str[0]))
		return (1);
	if (is_quote(str[0]))
	{
		quote = str[0];
		i++;
		while (str[i] && str[i] != quote)
			i++;
		return (i + 1);
	}
	while (str[i] && !is_symbol(str[i]) && str[i] != ' ')
		i++;
	return (i);
}

/**
 * This function free every array that was created before a malloc failure.
*/
void	ft_malloc_fail(char **strs, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}
