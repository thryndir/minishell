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

bool	has_redir_type(t_redir *redir, int type)
{
	t_redir *current;

	current = redir;
	while (current)
	{
		if ((int)current->type == type)
			return (1);
		current = current->next;
	}
	return (0);
}

void	parent(t_command *cmd, t_exec *exec, int depth)
{
	static int	pipe_fds[2];
	int			next_out;

	if (cmd->next)
		parent(cmd->next, exec, depth + 1);
	dprintf(2, "\nparent nbr : %d\n", depth);
	next_out = pipe_fds[1];
	if (cmd->index == exec->cmd_nbr - 1)
		next_out = -1;
	if (exec->cmd_nbr > 1)
		if (pipe(pipe_fds) == -1)
			ft_error("problem with a pipe");
	if (cmd->next && !has_redir_type(cmd->redirections, REDIR_OUT) // be carefull with append
		&& !has_redir_type(cmd->next->redirections, REDIR_IN))
		dup2(next_out, pipe_fds[1]);
	print_open_fds("parent before child");
	sleep(1);
	runner(cmd, exec, pipe_fds, next_out);
	print_open_fds("parent after child");
	verif_and_close(&next_out);
	verif_and_close(&pipe_fds[0]);
	if (cmd->index == 0)
		verif_and_close(&pipe_fds[1]);
	if (!(cmd->index))
	{
		hold_on(exec->pid, &(exec->status));
		if (WEXITSTATUS(exec->status))
			return_code(exec);
	}
}
