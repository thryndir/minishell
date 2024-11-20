/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgerbaul <jgerbaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 02:43:43 by jgerbaul          #+#    #+#             */
/*   Updated: 2024/11/15 23:11:55 by jgerbaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * This function call all the needed function to process a
 * *char and make a node for the linked list
 */
t_command	*parse_command(char **input, int i)
{
	t_command	*cmd;
	int			count;

	count = count_command_argv(input, i);
	cmd = init_command();
	if (!handle_argv(cmd, input, i, count))
	{
		free_commands(cmd);
		return (NULL);
	}
	if (!process_redirections(cmd, input, i, count))
	{
		free_commands(cmd);
		return (NULL);
	}
	return (cmd);
}

/**
 * Tokenizer main command, call the parse_command function to process
 * **input and return a linked list of commands
 */
t_command	*parse_input(char **input)
{
	t_command	*cmd_list;
	t_command	*new_cmd;
	int			i;

	cmd_list = NULL;
	i = 0;
	while (input[i])
	{
		new_cmd = parse_command(input, i);
		if (!add_command(&cmd_list, new_cmd))
		{
			free_commands(cmd_list);
			free_commands(new_cmd);
			return (NULL);
		}
		i++;
	}
	return (cmd_list);
}
