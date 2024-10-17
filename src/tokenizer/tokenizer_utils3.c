/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgerbaul <jgerbaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 22:54:06 by jgerbaul          #+#    #+#             */
/*   Updated: 2024/10/17 21:51:47 by jgerbaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * This function extract a word between quotes in the input string.
*/
char	*extract_quoted_word(const char *str, int *i, int len)
{
	int		k;
	char	*word;
	char	quote;

	k = 0;
	word = (char *)malloc((len + 1) * sizeof(char));
	if (word == NULL)
		return (NULL);
	quote = str[*i];
	word[k++] = str[(*i)++];
	while (str[*i] && str[*i] != quote)
		word[k++] = str[(*i)++];
	if (str[*i])
		word[k++] = str[(*i)++];
	word[k] = '\0';
	return (word);
}

/**
 * This function extract a word in the input string.
*/
char	*extract_regular_word(const char *str, int *i, int len)
{
	int		k;
	char	*word;

	k = 0;
	word = (char *)malloc((len + 1) * sizeof(char));
	if (word == NULL)
		return (NULL);
	while (k < len)
		word[k++] = str[(*i)++];
	word[k] = '\0';
	return (word);
}

/**
 *  This function extract word and use two other function to bypass
 * the 25 lines limit.
*/
char	*extract_word(const char *str, int *i, int *status)
{
	int		len;
	char	*word;

	len = ft_charnbr(str + *i);
	if (is_quote(str[*i]))
		word = extract_quoted_word(str, i, len);
	else
		word = extract_regular_word(str, i, len);
	if (word == NULL)
		*status = -1;
	return (word);
}

/**
 *  This function convert the input string to a **tab.
*/
char	**ft_str_to_array(char **strs, const char *str)
{
	int	i;
	int	j;
	int	status;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] && str[i] == ' ')
			i++;
		if (!str[i])
			break ;
		status = 0;
		strs[j] = extract_word(str, &i, &status);
		if (status == -1)
		{
			ft_malloc_fail(strs, j);
			return (NULL);
		}
		j++;
	}
	strs[j] = NULL;
	return (strs);
}

/**
 * Modified version of ft_split to help me tokenize the input string.
*/
char	**ft_mini_split(char const *str)
{
	char	**strs;
	int		word_count;

	if (str == NULL)
		return (NULL);
	word_count = ft_strnbr(str);
	strs = (char **)malloc((word_count + 1) * sizeof(char *));
	if (strs == NULL)
		return (NULL);
	return (ft_str_to_array(strs, str));
}
