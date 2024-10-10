

#include "minishell.h"

int cd_builtin(t_pipex *pipex)
{
	(void)pipex;
	ft_dprintf(2, "cd");
	exit(0);
} 