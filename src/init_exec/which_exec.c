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
	int prev_out;

	if (cmd->next)
		parent(cmd->next, exec, depth + 1);
	dprintf(2, "\nparent depth %d\n", depth);
	prev_out = pipe_fds[1];
	printf("fd = %d\n", prev_out);
	if (cmd->index != 0)
	{
		if (pipe(pipe_fds) == -1)
			ft_error("problem with a pipe");
	}
	int test[2];
	test[0] = pipe_fds[0];
	test[1] = prev_out;
	runner(cmd, exec, test);
	sleep(1);
	if (cmd->next)
		close(prev_out);
	close(pipe_fds[0]);
	if (!(cmd->index))
	{
		hold_on(exec->pid, &(exec->status));
		if (WEXITSTATUS(exec->status))
			return_code(exec);
	}
}
