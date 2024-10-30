#include "minishell.h"
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

void	ast_exec(t_node *node)
{
	return ;
}

void	linear_exec(t_node *node, t_exec *exec)
{
	t_node *current;

	current = node;
	redir_all(node);
	while (current)
	{
		if (current->type == NODE_CMD)
		{
			runner(&current->u_u.cmd, exec);
			exec->cmd_count++;
			current = current->u_u.cmd.node;
		}
		else
			current = current->u_u.redir.node;
	}
	close_pipe(exec->pipe_fd, exec->cmd_nbr);
	hold_on(exec->pid, &(exec->status));
	if (WEXITSTATUS(exec->status))
		return_code(exec);
}

void	linear_or_ast(t_node *node, t_exec *exec)
{
	if (node->type == NODE_PIPE)
        ast_exec(node);
	else
		linear_exec(node);
}