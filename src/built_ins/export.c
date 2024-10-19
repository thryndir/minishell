

#include "minishell.h"

int export_builtin(t_pipex *pipex)
{
	(void)pipex;
	ft_dprintf(2, "export");
	exit(0);
}