/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minisplit_utlis2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgerbaul <jgerbaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 22:51:49 by jgerbaul          #+#    #+#             */
/*   Updated: 2024/12/04 00:07:19 by jgerbaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "gcmalloc.h"

/**
 * Main word counter here, the other two are here because of
 * the 25 line restriction.
*/
int	count_word(const char *str, int *i)
{
	if (is_double_symbol(str, *i))
	{
		(*i) += 2;
		return (1);
	}
	if (is_symbol(str[*i]) && !is_quote(str[*i]))
	{
		(*i)++;
		return (1);
	}
	if (is_quote(str[*i]))
		return (count_quoted_word(str, i));
	if (str[*i] && !is_symbol(str[*i]) && !ft_isspace(str[*i]))
	{
		return (count_regular_word(str, i));
	}
	return (0);
}

/**
 * This function count the number a word in the input string.
*/
int	mini_strnbr(const char *str)
{
	int	result;
	int	i;

	result = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && ft_isspace(str[i]))
			i++;
		result += count_word(str, &i);
	}
	return (result);
}

/**
 * This function give back the number of char before specific
 * requirements (quote search).
*/
int	mini_charnbr(const char *str)
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
	while (str[i] && !is_symbol(str[i]) && !ft_isspace(str[i]))
		i++;
	return (i);
}

/**
 * This function free every array that was created before a malloc failure.
*/
void	mini_malloc_fail(char **strs, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		gc_free(strs[i]);
		i++;
	}
	gc_tab_free(strs);
}

/*
void	remove_quotes_from_argv(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (is_quote(argv[i][0])
			&& is_quote(argv[i][ft_strlen(argv[i]) - 1]))
		{
			argv[i]++;
			argv[i][ft_strlen(argv[i]) - 1] = '\0';
		}
		i++;
	}
}
*/

void	remove_quotes_from_argv(char **argv)
{
	int		i;
	char	*new_str;
	int		len;

	i = 0;
	while (argv[i])
	{
		len = ft_strlen(argv[i]);
		if (len > 1 && is_quote(argv[i][0]) && is_quote(argv[i][len - 1]))
		{
			new_str = gc_malloc(len - 1);
			ft_strlcpy(new_str, argv[i] + 1, len - 1);
			gc_free(argv[i]);
			argv[i] = new_str;
		}
		i++;
	}
}