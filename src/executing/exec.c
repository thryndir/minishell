/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 20:44:33 by lgalloux          #+#    #+#             */
/*   Updated: 2025/01/03 16:37:39 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"	

void	set_cmd_fd(int type, t_command *cmd, t_redir *redir, int *pipe_and_next)
{
	t_redir	*last;

	last = last_redir_type(type, redir);
	if (type == REDIR_IN && last)
	{
		cmd->fd_in = last->fd;
		verif_and_close(&pipe_and_next[IN]);
	}
	else if ((type == REDIR_OUT || type == REDIR_APPEND) && last)
	{
		cmd->fd_out = last->fd;
		verif_and_close(&pipe_and_next[OUT]);
	}
}

void	pipe_redir(t_command *cmd, t_exec exec, int *pipe_and_next)
{
	if (exec.cmd_nbr == 1)
		return ;
	verif_and_close(&pipe_and_next[OUT]);
	if (cmd->index == 0)
	{
		cmd->fd_out = pipe_and_next[NEXT];
		verif_and_close(&pipe_and_next[IN]);
	}
	else if (cmd->index == (exec.cmd_nbr - 1))
		cmd->fd_in = pipe_and_next[IN];
	else
	{
		cmd->fd_in = pipe_and_next[IN];
		cmd->fd_out = pipe_and_next[NEXT];
	}
}

void	redirect(t_command *cmd, t_exec *exec, int *pipe_and_next)
{
	t_redir	*current;

	current = cmd->redirections;
	while (current)
	{
		keep_fd(current, cmd, pipe_and_next);
		current = current->next;
	}
	pipe_redir(cmd, *exec, pipe_and_next);
	set_cmd_fd(REDIR_IN, cmd, cmd->redirections, pipe_and_next);
	set_cmd_fd(REDIR_OUT, cmd, cmd->redirections, pipe_and_next);
}

void	runner(t_command *cmd, t_exec *exec, int *pipe_and_next)
{
	t_builtin	*htable;
	char		**path;

	htable = htable_get(cmd->argv[0], ft_strlen(cmd->argv[0]));
	if (htable && exec->cmd_nbr == 1)
	{
		if (cmd->redirections)
			redirect_builtin(cmd, exec, pipe_and_next);
		htable->builtin_func(cmd, exec);
		if (cmd->redirections)
			restore_std(RESTORE);
	}
	else
	{
		fork_init(exec);
		if (ft_lstlast(exec->pid)->data == 0)
		{
			path = ft_split(get_value(exec->env, "PATH"), ':');
			if (!htable)
				cmd->path = find_path(path, cmd->argv[0], pipe_and_next);
			gc_tab_free(path);
			redirect(cmd, exec, pipe_and_next);
			child(exec, cmd);
		}
	}
}

void	child(t_exec *exec, t_command *cmd)
{
	char		**env;
	t_builtin	*htable;

	env = lst_to_array(exec->env);
	if (cmd->fd_in != -1)
		dup2(cmd->fd_in, STDIN_FILENO);
	if (cmd->fd_out != -1)
		dup2(cmd->fd_out, STDOUT_FILENO);
	verif_and_close(&cmd->fd_in);
	verif_and_close(&cmd->fd_out);
	htable = htable_get(cmd->argv[0], ft_strlen(cmd->argv[0]));
	if (htable)
	{
		htable->builtin_func(cmd, exec);
		gc_free_all();
		exit(g_exit_code);
	}
	else
		execve(cmd->path, cmd->argv, env);
	execve_fail(cmd);
}
