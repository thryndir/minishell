/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_node_initializer.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgerbaul <jgerbaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 01:31:32 by jgerbaul          #+#    #+#             */
/*   Updated: 2024/11/12 01:35:41 by jgerbaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * redir node initialization
 */
t_redir	*init_redir(void)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = REDIR_IN;
	redir->file = NULL;
	redir->fd = -1;
	redir->next = NULL;
	return (redir);
}

/**
 * command node initialization
 */
t_command	*init_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->name = NULL;
	cmd->args = NULL;
	cmd->argc = 0;
	cmd->fd_in = -1;
	cmd->fd_out = -1;
	cmd->index = -1;
	cmd->path = NULL;
	cmd->redirections = NULL;
	cmd->next = NULL;
	return (cmd);
}

/**
 * This function is used to append a redirection (*new_redir) to the right
 * field of a command node, or if there is already one it
 * can append the redirection as the *next field of the existing
 * redir node
 */
int	add_redir(t_command *cmd, t_redir *new_redir)
{
	t_redir	*current;

	if (!cmd->redirections)
	{
		cmd->redirections = new_redir;
		return (1);
	}
	current = cmd->redirections;
	while (current->next)
		current = current->next;
	current->next = new_redir;
	return (1);
}

/**
 * This function is used to either create a new linked list
 * of command or append the new command node as the *next
 * field of an other command node
 */
int	add_command(t_command **cmd_list, t_command *new_cmd)
{
	t_command	*current;
	int			index;

	if (!*cmd_list)
	{
		*cmd_list = new_cmd;
		new_cmd->index = 0;
		return (1);
	}
	current = *cmd_list;
	index = 1;
	while (current->next)
	{
		current = current->next;
		index++;
	}
	current->next = new_cmd;
	new_cmd->index = index;
	return (1);
}
