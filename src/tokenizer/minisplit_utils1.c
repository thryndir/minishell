/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minisplit_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgerbaul <jgerbaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 22:54:54 by jgerbaul          #+#    #+#             */
/*   Updated: 2024/12/09 16:44:01 by jgerbaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * This function return a boolean wether the input char is a quote or not.
*/
bool	is_quote(char c)
{
	if (c == '"' || c == '\'')
		return (true);
	else
		return (false);
}

/**
 * This function return a boolean wether the input char is a symbol or not.
*/
bool	is_symbol(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (true);
	else
		return (false);
}

/**
 * This function return a boolean wether the input char and the one
 * right after it is a double-quote or not.
*/
bool	is_double_symbol(const char *str, int i)
{
	if ((str[i] == '<' && str[i + 1] == '<')
		|| (str[i] == '>' && str[i + 1] == '>'))
		return (true);
	else
		return (false);
}

/**
 * This function count quoted word within the string and increment the int
 * pointer when it found one.
*/
bool	count_quoted_word(const char *str, int *i)
{
	int	simple_q;
	int	double_q;

	simple_q = 0;
	double_q = 0;
	while (str[*i])
	{
		quote_count(str[*i], &simple_q, &double_q);
		(*i)++;
		if (!(simple_q % 2) && !(double_q % 2)
			&& (is_symbol(str[*i]) || ft_isspace(str[*i])))
			break ;
	}
	return (true);
}

/**
 * This function count non-quoted word within the string and increment the int
 * pointer when it found one.
*/
bool	count_regular_word(const char *str, int *i)
{
	while (str[*i] && !is_symbol(str[*i]) && !ft_isspace(str[*i]))
		(*i)++;
	return (true);
}
