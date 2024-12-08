/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_redirections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgerbaul <jgerbaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 23:59:24 by jgerbaul          #+#    #+#             */
/*   Updated: 2024/12/08 23:10:35 by jgerbaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "gcmalloc.h"

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
		gc_free(redir);
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
	if (redir->file && (redir->file[0] == '\'' || redir->file[0] == '"'))
		redir->file = remove_quotes_from_file(redir->file);
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

char	*remove_quotes_from_file(char *str)
{
	char	*new_str;
	int		len;

	new_str = NULL;
	len = ft_strlen(str);
	if (len > 1 && is_quote(str[0]) && is_quote(str[len - 1]))
	{
		new_str = gc_malloc(len - 1);
		ft_strlcpy(new_str, &str[1], len - 1);
		gc_free(str);
	}
	return (new_str);
}
