#include "executing.h"

void    redirect_builtin(t_command *cmd, t_exec *exec, int *pipe_fds, int next_out)
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

void		close_prev_open(t_redir *to_comp, t_redir *redir)
{
	t_redir *current = redir;
	
	while (current)
	{
		if (!ft_strcmp(current->file, to_comp->file) && current->fd != -1)
			verif_and_close(&current->fd);
		current = current->next;
	}
}

void	keep_fd(t_redir *redir, t_command *cmd, int pipe_fds[2], int next_out)
{
	char	*last_file;

	last_file = NULL;
	close_prev_open(redir, cmd->redirections);
	last_file = last_fd_type(redir->type, cmd, cmd->redirections, pipe_fds);
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
		}
	if (last_file && ft_strcmp(redir->file, last_file))
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