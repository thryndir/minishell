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

void	parent(t_command *cmd, t_exec *exec)
{
	t_command *current;

	if (current->next)
		parent(cmd->next, exec);
	runner(cmd, exec);
	if (!cmd->index)
	{
		close_pipe(cmd);
		hold_on(exec->pid, &(exec->status));
		if (WEXITSTATUS(exec->status))
			return_code(exec);
	}
}
