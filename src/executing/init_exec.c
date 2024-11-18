#include "executing.h"

void	fork_init(t_exec *exec)
{
	ft_lstadd_back(&(exec->pid), ft_lstnew(-1));
	ft_lstlast(exec->pid)->data = fork();
	if (ft_lstlast(exec->pid)->data == -1)
		ft_error("problem with the fork: ", 1, exit_code);
}

char	*this_is_the_path(char **path, char *cmd)
{
	char	*cmd_path;
	int		i;

	i = 0;
	if (cmd == NULL)
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	while (path[i])
	{
		cmd_path = ft_strsjoin(3, path[i], "/", cmd);
		if (cmd_path == NULL)
			return (NULL);
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		else
			gc_free(cmd_path);
		i++;
	}
	return (NULL);
}
