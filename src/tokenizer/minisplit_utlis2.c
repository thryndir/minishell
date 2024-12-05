/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minisplit_utlis2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgerbaul <jgerbaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 22:51:49 by jgerbaul          #+#    #+#             */
/*   Updated: 2024/12/05 19:26:00 by jgerbaul         ###   ########.fr       */
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


static int	count_quoted(const char *str, int *i, char quote)
{
	int	len;

	len = 0;
	(*i)++;
	while (str[*i] && str[*i] != quote)
	{
		len++;
		(*i)++;
	}
	(*i)++;
	return (len);
}

/**
 * This function give back the number of char before specific
 * requirements (quote search).
*/
int	mini_charnbr(const char *str)
{
   int	len;
   int	i;
   
   i = 0;
   len = 0;
   if (is_double_symbol(str, 0))
	   return (2);
   if (is_symbol(str[0]) && !is_quote(str[0]))
	   return (1); 
   while (str[i] && (!is_symbol(str[i]) || is_quote(str[i])))
   {
	   if (is_quote(str[i]))
		   len += count_quoted(str, &i, str[i]);
	   else if (!ft_isspace(str[i]))
	   {
		   len++;
		   i++;
	   }
	   else
		   break ;
   }
   return (len);
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
