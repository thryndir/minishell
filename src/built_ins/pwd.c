

#include "minishell.h"

int pwd_builtin(t_pipex *pipex)
{
	(void)pipex;
	char *str;
	str = NULL;
	ft_dprintf(2, "%s\n", getcwd(str, 0));
	exit(0);
}