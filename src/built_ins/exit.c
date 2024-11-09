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
	(void)exec;
	if (cmd->argv[2])
	{
		ft_printf("minishell: exit: too many arguments");
		return (1);
	}
	else if (!cmd->argv[1])
	{
		exit(0);
	}
	else if (is_only_digit(cmd->argv[1]))
	{
		exit(ft_atoull(cmd->argv[1]));
	}
	else
	{
		ft_printf("minishell: exit: %s: numeric argument required",
			cmd->argv[1]);
		exit (2);
	}
}
