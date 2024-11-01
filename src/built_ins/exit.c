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

int	exit_builtin(t_pipex *pipex)
{
	if (pipex->cmds[2])
	{
		ft_printf("minishell: exit: too many arguments");
		return (1);
	}
	else if (!pipex->cmds[1])
	{
		free_all(pipex, FREE_LST);
		exit(0);
	}
	else if (is_only_digit(pipex->cmds[1]))
	{
		free_all(pipex, FREE_LST);
		exit(ft_atoull(pipex->cmds[1]));
	}
	else
	{
		ft_printf("minishell: exit: %s: numeric argument required",
			pipex->cmds[1]);
		free_all(pipex, FREE_LST);
		exit (2);
	}
}
