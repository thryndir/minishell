

#include "minishell.h"

int env_builtin(t_pipex *pipex)
{
	while (pipex->env)
	{
		ft_dprintf(2, "%s", pipex->env->name);
		write(2, "=", 1);
		ft_dprintf(2, "%s", pipex->env->value);
		write(2, "\n", 1);
		pipex->env = pipex->env->next;
	}
	exit(0);
}