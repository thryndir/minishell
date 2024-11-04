#include "executing.h"

int	is_only_c(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != c)
			return (0);
		i++;
	}
	return (1);
}

int	echo_builtin(t_command *cmd, t_exec *exec)
{
	int		i;
	bool	newline;

	i = 1;
	(void)exec;
	newline = 1;
	if (is_only_c(cmd->args[1] + 1, 'n'))
	{
		newline = 0;
		i = 2;
	}
	while (cmd->args[i])
	{
		ft_printf("%s ", cmd->args[i++]);
		if (cmd->args[i] && cmd->args[i + 1] == NULL)
			ft_printf("%s", cmd->args[i++]);
	}
	if (newline)
		write(1, "\n", 1);
	return (0);
}
