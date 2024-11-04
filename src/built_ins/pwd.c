#include "executing.h"

int	pwd_builtin(t_command *cmd, t_exec *exec)
{
	(void)cmd;
	ft_dprintf(2, "%s\n", get_value(exec->env, "PWD"));
	return (0);
}
