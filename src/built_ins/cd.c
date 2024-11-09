#include "executing.h"

int	cd_builtin(t_command *cmd, t_exec *exec)
{
	char	*path;
	int		to_free;

	to_free = 0;
	if (cmd->argv[1] && (cmd->argv[1][0] == '~'
		|| !ft_strncmp("/home", cmd->argv[1], 5)))
		path = cmd->argv[1];
	else
	{
		path = ft_strsjoin(3, get_value(exec->env, "PWD"),
				"/", cmd->argv[1]);
		to_free = 1;
	}
	chdir(cmd->argv[1]);
	add_in_env(exec->env, "PWD", path);
	if (to_free)
		free(path);
	return (0);
}
