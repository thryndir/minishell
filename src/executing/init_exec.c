#include "executing.h"

void	fork_init(t_exec *exec)
{
	ft_lstadd_back(&(exec->pid), ft_lstnew(-1));
	ft_lstlast(exec->pid)->data = fork();
	if (ft_lstlast(exec->pid)->data == -1)
		ft_error("problem with the fork: ", exec, FREE_LST, 1);
}

char	*this_is_the_path(t_exec *exec, char **p_path, char **cmd)
{
	char	*path;
	char	*tmp;
	int		i;

	i = 0;
	if (cmd[0] == NULL)
		return (NULL);
	if (access(cmd[0], X_OK) == 0)
		return (ft_strdup(cmd[0]));
	while (p_path[i])
	{
		tmp = ft_strjoin("/", cmd[0]);
		if (tmp == NULL)
			ft_error("malloc failed\n", exec, -FREE_CMD, 1);
		path = ft_strjoin(p_path[i], tmp);
		if (path == NULL)
			return (NULL);
		free(tmp);
		if (access(path, X_OK) == 0)
			return (path);
		else
			free(path);
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
