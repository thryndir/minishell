#include "executing.h"
#include "parsing.h"

// void	execution(t_cmd *cmd)
// {
// 	if (premier token est un builtin)
// 		execute_builtin(...);
// 	else
// 		execute(...);
// 	if (cmd->pipe)
// 		execute_pipe(cmd->pipe);
// }

void	parent(t_command *cmd, t_exec *exec, int depth)
{
	static int	pipe_fds[2];

	if (cmd->next)
		parent(cmd->next, exec, depth + 1);
	dprintf(2, "\nparent depth %d\n", depth);
	if (pipe(pipe_fds) == -1)
		ft_error("problem with a pipe");
	runner(cmd, exec, pipe_fds);
	sleep(1);
	close(pipe_fds[0]);
	if (!(cmd->index))
	{
		hold_on(exec->pid, &(exec->status));
		if (WEXITSTATUS(exec->status))
			return_code(exec);
	}
}
