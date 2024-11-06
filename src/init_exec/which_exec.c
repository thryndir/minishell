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
	if (pipe(pipe_fds) == -1)
		ft_error("problem with a pipe");
	runner(cmd, exec, pipe_fds);
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	if (!(cmd->index))
	{
		close_all(cmd, CMD);
		hold_on(exec->pid, &(exec->status));
		if (WEXITSTATUS(exec->status))
			return_code(exec);
	}
}
