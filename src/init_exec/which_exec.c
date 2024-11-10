#include "executing.h"
#include "parsing.h"

int		verif_and_close(int *fd)
{
	int result;

	result = -1;
	if (*fd != -1)
		close(*fd);
	*fd = -1;
	return (result);
}


void	parent(t_command *cmd, t_exec *exec, int depth)
{
	static int	pipe_fds[2];
	int			next_out;

	if (cmd->next)
		parent(cmd->next, exec, depth + 1);
	dprintf(2, "\nparent depth %d\n", depth);
		next_out = pipe_fds[1];
	if (cmd->index == exec->cmd_nbr - 1)
		next_out = -1;
	if (exec->cmd_nbr > 1)
		if (pipe(pipe_fds) == -1)
			ft_error("problem with a pipe");
	if (cmd->index != exec->cmd_nbr - 1)
		dup2(next_out, pipe_fds[1]);
	print_open_fds("parent process before child");
	runner(cmd, exec, pipe_fds, next_out);
	// if (cmd->index != exec->cmd_nbr - 1)
	// 	verif_and_close(&pipe_fds[1]);
	sleep(1);
	verif_and_close(&next_out);
	verif_and_close(&pipe_fds[0]);
	if (cmd->index == 0)
		verif_and_close(&pipe_fds[1]);
	print_open_fds("parent process after child");
	if (!(cmd->index))
	{
		hold_on(exec->pid, &(exec->status));
		if (WEXITSTATUS(exec->status))
			return_code(exec);
	}
}
