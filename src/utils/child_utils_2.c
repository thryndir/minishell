/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:12:38 by thryndir          #+#    #+#             */
/*   Updated: 2024/12/11 14:46:09 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

t_redir	*last_redir_type(int type, t_redir *redir)
{
	t_redir			*current;
	t_redir			*last;
	t_redir_type	kind;

	current = redir;
	last = NULL;
	if (type == REDIR_IN || type == REDIR_HEREDOC)
		kind = REDIR_IN;
	else if (type == REDIR_APPEND || type == REDIR_OUT)
		kind = REDIR_OUT;
	while (current)
	{
		if (kind == REDIR_IN)
			if (current->type == REDIR_IN || current->type == REDIR_HEREDOC)
				last = current;
		if (kind == REDIR_OUT)
			if (current->type == REDIR_OUT || current->type == REDIR_APPEND)
				last = current;
		current = current->next;
	}
	return (last);
}

void	redirect_builtin(t_command *cmd, t_exec *exec, int *pipe_fds
	, int next_out)
{
	redirect(cmd, exec, pipe_fds, next_out);
	restore_std(SAVE);
	if (cmd->fd_in != -1)
		dup2(cmd->fd_in, STDIN_FILENO);
	if (cmd->fd_out != -1)
		dup2(cmd->fd_out, STDOUT_FILENO);
	verif_and_close(&cmd->fd_in);
	verif_and_close(&cmd->fd_out);
}

void	close_prev_open(t_redir *to_comp, t_redir *redir)
{
	t_redir	*current;

	current = redir;
	while (current)
	{
		if (!ft_strcmp(current->file, to_comp->file) && current->fd != -1)
			verif_and_close(&current->fd);
		current = current->next;
	}
}

void	keep_fd(t_redir *redir, t_command *cmd, int pipe_fds[2], int next_out)
{
	t_redir	*last;

	close_prev_open(redir, cmd->redirections);
	last = last_redir_type(redir->type, cmd->redirections);
	if (redir->type == REDIR_IN)
		redir->fd = read_or_write(READ, redir);
	else if (redir->type == REDIR_OUT || redir->type == REDIR_APPEND)
		redir->fd = read_or_write(WRITE, redir);
	if (redir->fd == -1)
	{
		print_error("minishell", strerror(errno), g_exit_code);
		verif_and_close(&pipe_fds[0]);
		verif_and_close(&pipe_fds[1]);
		verif_and_close(&next_out);
		gc_free_all();
		exit(g_exit_code);
	}
	if (last && ft_strcmp(redir->file, last->file))
		verif_and_close(&redir->fd);
}

void	restore_std(int save_or_restore)
{
	static int	std[2];

	if (save_or_restore == SAVE)
	{
		std[0] = dup(STDIN_FILENO);
		std[1] = dup(STDOUT_FILENO);
	}
	else if (save_or_restore == RESTORE)
	{
		dup2(std[0], STDIN_FILENO);
		dup2(std[1], STDOUT_FILENO);
		verif_and_close(&std[0]);
		verif_and_close(&std[1]);
	}
}
