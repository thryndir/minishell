/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   browse.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:53:57 by lgalloux          #+#    #+#             */
/*   Updated: 2024/12/10 16:32:50 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"
#include "parsing.h"

int	verif_and_close(int *fd)
{
	int	result;

	result = -1;
	if (*fd != -1 && *fd > 2)
		close(*fd);
	*fd = -1;
	return (result);
}

bool	has_redir_type(t_redir *redir, int type)
{
	t_redir	*current;

	current = redir;
	while (current)
	{
		if (type == REDIR_IN && ((int)current->type == REDIR_IN
				|| (int)current->type == REDIR_HEREDOC))
			return (true);
		else if (type == REDIR_OUT && ((int)current->type == REDIR_OUT
				|| (int)current->type == REDIR_APPEND))
			return (true);
		current = current->next;
	}
	return (false);
}

void	parent(t_command *cmd, t_exec *exec, int depth)
{
	static int	pipe_fds[2];
	int			next_out;

	if (cmd->next)
		parent(cmd->next, exec, depth + 1);
	next_out = pipe_fds[1];
	if (cmd->index == exec->cmd_nbr - 1)
		next_out = -1;
	pipe_fds[0] = 0;
	if (exec->cmd_nbr > 1)
		if (pipe(pipe_fds) == -1)
			print_error("problem with a pipe", strerror(errno), errno);
	if (cmd->next && !has_redir_type(cmd->redirections, REDIR_OUT)
		&& !has_redir_type(cmd->next->redirections, REDIR_IN))
		dup2(next_out, pipe_fds[1]);
	runner(cmd, exec, pipe_fds, next_out);
	verif_and_close(&next_out);
	verif_and_close(&pipe_fds[0]);
	if (cmd->index == 0)
		verif_and_close(&pipe_fds[1]);
	if (!(cmd->index) && exec->pid)
		hold_on(exec->pid);
}
