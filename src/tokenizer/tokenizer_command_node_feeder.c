/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_command_node_feeder.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgerbaul <jgerbaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 23:20:02 by jgerbaul          #+#    #+#             */
/*   Updated: 2024/12/07 00:52:17 by jgerbaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "gcmalloc.h"

/**
 * This function count and return the number
 * of argv in a signle command
 */
int	count_command_argv(char **input, int index)
{
	int	count;

	count = 0;
	while (input[index + count] && ft_strcmp(input[index + count], "|"))
	{
		if (is_redirect(input[index + count]))
		{
			if (!input[index + count + 1])
				return (count);
			count += 2;
		}
		else
			count++;
	}
	return (count);
}

/**
 * Create and handle the argv field of the command node
 */
int	handle_argv(t_command *cmd, char **input, int start, int count)
{
	int	i;
	int	argv_index;

	cmd->argv = gc_malloc(sizeof(char *) * (count + 1));
	i = 0;
	argv_index = 0;
	while (i < count)
	{
		if (is_redirect(input[start + i]) && input[start + i][0] != '"')
			i += 2;
		else
		{
			cmd->argv[argv_index] = mini_strdup(input[start + i]);
			if (!cmd->argv[argv_index])
				return (0);
			argv_index++;
			i++;
		}
	}
	cmd->argv[argv_index] = NULL;
	cmd->argc = argv_index;
	return (1);
}
