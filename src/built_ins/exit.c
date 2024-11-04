#include "executing.h"

int	is_only_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	exit_builtin(t_command *cmd, t_exec *exec)
{
	if (cmd->args[2])
	{
		ft_printf("minishell: exit: too many arguments");
		return (1);
	}
	else if (!cmd->args[1])
	{
		free_all(exec, FREE_LST);
		exit(0);
	}
	else if (is_only_digit(cmd->args[1]))
	{
		free_all(exec, FREE_LST);
		exit(ft_atoull(cmd->args[1]));
	}
	else
	{
		ft_printf("minishell: exit: %s: numeric argument required",
			cmd->args[1]);
		free_all(exec, FREE_LST);
		exit (2);
	}
}
