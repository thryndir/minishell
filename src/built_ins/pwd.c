#include "executing.h"

int	pwd_builtin(t_pipex *pipex)
{
	ft_dprintf(2, "%s\n", get_value(pipex->env, "PWD"));
	return (0);
}
