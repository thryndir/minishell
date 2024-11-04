#include "executing.h"

int	cd_builtin(t_command *cmd, t_exec *exec)
{
	char	*path;
	int		to_free;

	to_free = 0;
	if (cmd->args[1] && (cmd->args[1][0] == '~'
		|| !ft_strncmp("/home", cmd->args[1], 5)))
		path = cmd->args[1];
	else
	{
		path = ft_strsjoin(3, get_value(exec->env, "PWD"),
				"/", cmd->args[1]);
		to_free = 1;
	}
	chdir(cmd->args[1]);
	add_in_env(exec->env, "PWD", path);
	if (to_free)
		free(path);
	return (0);
}
