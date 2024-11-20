/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_memory_cleaning.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgerbaul <jgerbaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 01:23:47 by jgerbaul          #+#    #+#             */
/*   Updated: 2024/11/15 23:11:57 by jgerbaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "gcmalloc.h"

/**
 * This function free the redir node and it's member
 * also closing any fd that could be open
 */
void	free_redirs(t_redir *redir)
{
	t_redir	*temp;

	while (redir)
	{
		temp = redir->next;
		if (redir->file)
			gc_free(redir->file);
		if (redir->fd > 2)
			close(redir->fd);
		gc_free(redir);
		redir = temp;
	}
}

/**
 * This function free the argv member of the command node
 */
void	free_command_argv(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		gc_free(argv[i]);
		i++;
	}
	gc_free(argv);
}

/**
 * This function free the command node
 */
void	free_commands(t_command *cmd)
{
	t_command	*temp;

	while (cmd)
	{
		temp = cmd->next;
		if (cmd->path)
			gc_free(cmd->path);
		if (cmd->argv)
			free_command_argv(cmd->argv);
		if (cmd->fd_in > 2)
			close(cmd->fd_in);
		if (cmd->fd_out > 2)
			close(cmd->fd_out);
		free_redirs(cmd->redirections);
		gc_free(cmd);
		cmd = temp;
	}
}
