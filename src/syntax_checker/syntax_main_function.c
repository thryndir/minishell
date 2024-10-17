/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_main_function.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgerbaul <jgerbaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 22:44:35 by jgerbaul          #+#    #+#             */
/*   Updated: 2024/10/17 21:52:08 by jgerbaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * This function check is an operator is misplaced and
 * ignore operators that are beetwin quotes.
*/
bool	misplaced_operators(const char *input)
{
	int	command;
	int	*simple_q;
	int	*double_q;

	simple_q = 0;
	double_q = 0;
	command = 0;
	if (*input == '|' || *input == '&')
		return (true);
	while (*input)
	{
		quote_count(*input, simple_q, double_q);
		if (*input == '|' && !(*(simple_q) % 2) && !(*(double_q) % 2))
		{
			if (command)
				return (true);
			command = 1;
		}
		else if (!ft_isspace(*input))
			command = 0;
		input++;
	}
	if (command)
		return (true);
	return (false);
}

/**
  * Main redir checker it ensure that redirection are used correctly.
 */
bool	check_invalid_redirection(const char *input)
{
	int		simple_q;
	int		double_q;
	char	redir;

	simple_q = 0;
	double_q = 0;
	while (*input)
	{
		quote_count(*input, &simple_q, &double_q);
		if (!(simple_q % 2) && !(double_q % 2)
			&& (*input == '<' || *input == '>'))
		{
			redir = *input;
			input++;
			if (check_after_redir(&input, redir))
				return (true);
			continue ;
		}
		input++;
	}
	return (false);
}

/**
 * This function search for the invalid operators such as
 * '||' '&&' ';' '\\'.
*/
bool	invalid_operators(const char *input)
{
	int							simple_q;
	int							double_q;

	simple_q = 0;
	double_q = 0;
	while (*input)
	{
		quote_count(*input, &simple_q, &double_q);
		if (!(double_q % 2) && !(simple_q % 2)
			&& (((*input == '&' && *(input + 1) == '&')
					|| (*input == '|' && *(input + 1) == '|'))
				|| *input == ';' || *input == '\\'))
			return (true);
		input++;
	}
	return (false);
}

/**
 * This function check if the quotes comes
 * by two wich would mean that they are closed
*/
bool	unclosed_quotes(const char *input)
{
	char	quote;

	quote = 0;
	while (*input)
	{
		if (*input == '\'' || *input == '\"')
		{
			if (quote == *input)
				quote = 0;
			else if (quote == 0)
				quote = *input;
		}
		input++;
	}
	if (quote == 0)
		return (false);
	else
		return (true);
}

/**
 * Main syntax error it combine every syntax function to ensure that
 * minishell only get the right input to work with.
*/
bool	syntax_errors(const char *input)
{
	const char	*tmp;
	bool		empty;

	if (!input)
		return (true);
	tmp = input;
	empty = true;
	while (*tmp && empty)
	{
		if (!ft_isspace(*tmp))
			empty = false;
		tmp++;
	}
	if (empty || unclosed_quotes(input) || invalid_operators(input)
		|| misplaced_operators(input) || check_invalid_redirection(input))
		return (true);
	return (false);
}
