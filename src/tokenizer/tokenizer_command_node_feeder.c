/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_command_node_feeder.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgerbaul <jgerbaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 23:20:02 by jgerbaul          #+#    #+#             */
/*   Updated: 2024/11/15 23:11:56 by jgerbaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * This function count and return the number
 * of args in a signle command
 */
int	count_command_args(char **input, int index)
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
 * This function copy the command arguments in the
 * args field of the command node
 */
int	copy_arg(t_command *cmd, char **input, int *start, int *arg_index)
{
	cmd->args[*arg_index] = mini_strdup(input[*start]);
	if (!cmd->args[*arg_index])
		return (0);
	(*arg_index)++;
	(*start)++;
	return (1);
}

/**
 * Create and handle the args field of the command node
 */
int	handle_args(t_command *cmd, char **input, int start, int count)
{
	int	i;
	int	args_index;

	cmd->args = gc_malloc(sizeof(char *) * (count + 1));
	i = 0;
	args_index = 0;
	while (i < count)
	{
		if (is_redirect(input[start + i]))
			i += 2;
		else if (!copy_arg(cmd, input, &i, &args_index))
			return (0);
	}
	cmd->args[args_index] = NULL;
	cmd->argc = args_index;
	return (1);
}
