/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgerbaul <jgerbaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 22:43:19 by jgerbaul          #+#    #+#             */
/*   Updated: 2024/10/17 21:52:13 by jgerbaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * This function check the input character to see whether it's a
 * space (or equivalent character) or something else.
*/
bool	ft_isspace(char c)
{
	if (c == ' ' || c == '\f' || c == '\n' || c == '\r'
		|| c == '\t' || c == '\v')
		return (true);
	else
		return (false);
}

/**
 * This function act as a quote counter, it take a character in
 * entry and check whether it's a quote or a double quote and increment
 * simple_q or double_q according to that.
*/
void	quote_count(char c, int *simple_q, int *double_q)
{
	if (c == '\"')
		double_q++;
	if (c == '\'')
		simple_q++;
}

/**
 * This function check if the current char is a
 * redir pipe or null character.
*/
bool	is_symbol_or_nullchar(char c)
{
	return (c == '<' || c == '>' || c == '|' || c == '\0');
}

/**
 * This function is used when encountering a redir < or >
 * and check if the following character is the same redir
 * or another symbol.
*/
bool	check_after_redir(const char **input, char redir)
{
	if (**input == redir)
		(*input)++;
	while (**input && ft_isspace(**input))
		(*input)++;
	return (is_symbol_or_nullchar(**input));
}
