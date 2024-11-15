/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgerbaul <jgerbaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 02:43:43 by jgerbaul          #+#    #+#             */
/*   Updated: 2024/11/14 02:05:59 by jgerbaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * This function call all the needed function to process a
 * *char and make a node for the linked list
 */
t_command	*parse_command(char **input, int *index)
{
	t_command	*cmd;
	int			count;

	count = count_command_args(input, *index);
	cmd = init_command();
	if (!handle_args(cmd, input, *index, count))
	{
		free_commands(cmd);
		return (NULL);
	}
	if (!process_redirections(cmd, input, *index, count))
	{
		free_commands(cmd);
		return (NULL);
	}
	*index += count;
	if (input[*index] && !ft_strcmp(input[*index], "|"))
		(*index)++;
	return (cmd);
}

/**
 * Tokenizer main command, call the parse_command function to process
 * **input and return a linked list of commands
 * if needed can free th linked_list and the current node
 * the *index parameter will give the number of command
 */
t_command	*parse_input(char **input, int *index)
{
	t_command	*cmd_list;
	t_command	*new_cmd;

	cmd_list = NULL;
	index = 0;
	while (input[*index])
	{
		new_cmd = parse_command(input, index);
		if (!add_command(&cmd_list, new_cmd))
		{
			free_commands(cmd_list);
			free_commands(new_cmd);
			return (NULL);
		}
	}
	return (cmd_list);
}
