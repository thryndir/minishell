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

void	linear_exec(t_node *node)
{
	t_node *current;

	current = node;
	redir_all(node);
	while (current)
	{
		if (current->type == NODE_CMD && !current->u_u.cmd.builtin)
			exec_cmd(current->u_u.cmd);
		else if (current->type == NODE_CMD && current->u_u.cmd.builtin)
			exec_builtin(current->u_u.cmd);
		if (current->type == NODE_CMD)
			current = current->u_u.redir.node;
		else
			current = current->u_u.redir.node;
		current = 
	}
}

void	linear_or_ast(t_node *node)
{
	if (node->type == NODE_PIPE)
        ast_exec(node);
	else
		linear_exec(node);
}