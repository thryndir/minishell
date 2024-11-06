#include "executing.h"

void	fork_init(t_exec *exec)
{
	ft_lstadd_back(&(exec->pid), ft_lstnew(-1));
	ft_lstlast(exec->pid)->data = fork();
	if (ft_lstlast(exec->pid)->data == -1)
		ft_error("problem with the fork: ");
}

char	*this_is_the_path(char **path, char *cmd)
{
	char	*cmd_path;
	int		i;

	i = 0;
	if (cmd == NULL)
		return (NULL);
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	while (path[i])
	{
		cmd_path = ft_strsjoin(3, path[i], "/", cmd);
		if (cmd_path == NULL)
			return (NULL);
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		else
			free(cmd_path);
		i++;
	}
	return (NULL);
}

// void	init_exec(t_exec *exec, char *cmd)
// {
// 	if (exec->cmd != NULL)
// 		double_array_free(exec->cmd);
// 	exec->cmd = ft_split(cmd, ' ');
// 	if (exec->cmd == NULL)
// 		ft_error("problem with the first split\n", exec, -FREE_PIPE, 1);
// 	if (exec->path != NULL)
// 		free(exec->path);
// 	exec->cmd->path = this_is_the_path(exec, exec->p_path, exec->cmd);
// }
