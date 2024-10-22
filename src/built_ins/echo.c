#include "minishell.h"

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

int	echo_builtin(t_pipex *pipex)
{
	int		i;
	bool	newline;

	i = 1;
	newline = 1;
	if (is_only_c(pipex->cmds[1] + 1, 'n'))
	{
		newline = 0;
		i = 2;
	}
	while (pipex->cmds[i])
	{
		ft_printf("%s ", pipex->cmds[i++]);
		if (pipex->cmds[i] && pipex->cmds[i + 1] == NULL)
			ft_printf("%s", pipex->cmds[i++]);
	}
	if (newline)
		write(1, "\n", 1);
	return (0);
}
