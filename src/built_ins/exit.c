

#include "minishell.h"

int exit_builtin(t_pipex *pipex)
{
	(void)pipex;
	ft_dprintf(2, "exit");
	exit(0);
}