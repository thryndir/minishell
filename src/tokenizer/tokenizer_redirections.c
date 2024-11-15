/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_redirections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgerbaul <jgerbaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 23:59:24 by jgerbaul          #+#    #+#             */
/*   Updated: 2024/11/15 00:36:05 by jgerbaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * This function create a new redirection 
 * node and initialize it's value
 */
t_redir	*create_redir(const char *op, const char *file)
{
	t_redir			*redir;
	t_redir_type	type;

	type = get_redir_type(op);
	redir = init_redir();
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->file = mini_strdup(file);
	if (!redir->file)
	{
		free(redir);
		return (NULL);
	}
	return (redir);
}

/**
 * This function process a redirection calling
 * create_redir and feeding it's field
 */
int	process_one_redirection(t_command *cmd, char **input, int *i, int start)
{
	t_redir	*redir;

	redir = create_redir(input[start + *i], input[start + *i + 1]);
	if (!redir)
		return (0);
	if (!add_redir(cmd, redir))
		return (0);
	*i += 2;
	return (1);
}

/**
 * This function is the main redirection it check if the redirection have an
 * argument and call the necessary function to handle that task
 */
int	process_redirections(t_command *cmd, char **input, int start, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (is_redirect(input[start + i]))
		{
			if (i + 1 >= count)
				return (0);
			if (!process_one_redirection(cmd, input, &i, start))
				return (0);
		}
		else
			i++;
	}
	return (1);
}
