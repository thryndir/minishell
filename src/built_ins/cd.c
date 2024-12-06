/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:49:45 by lgalloux          #+#    #+#             */
/*   Updated: 2024/12/06 18:44:55 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

int	verif_dir(char *args)
{
	if (chdir(args) != 0)
	{
		print_error("cd", strerror(errno), errno);
		return (errno);
	}
	return (0);
}

char *revtrim(char *str, char *to_trim)
{
	int		start;
	int		size;

	start = 0;
	size = ft_strlen(str);
	while (size >= 0)
	{
		if (!strcmp(&str[size], to_trim))
			break;
		size--;
	}
	return(ft_substr(str, start, size));
}

void	cd_builtin(t_command *cmd, t_exec *exec)
{
	char	*path;
	char	*pwd;
	bool	to_free;

	to_free = 0;
	pwd = get_value(exec->env, "PWD");
	add_in_env(exec->env, "OLDPWD", pwd);
	if (verif_dir(cmd->argv[1]))
		return ;
	if ((cmd->argv[1][0] == '~' || !ft_strncmp("/home", cmd->argv[1], 5)))
		path = cmd->argv[1];
	else if (cmd->argv[1][0] == '-')
		path = get_value(exec->env, "OLDPWD");
	else if (!ft_strcmp(cmd->argv[1], ".."))
	{
		path = revtrim(pwd, ft_strrchr(pwd, '/'));
		to_free = true;
		if (!path[0])
			path = pwd;
	}
	else
		path = ft_strsjoin(3, pwd, "/", cmd->argv[1]);
	add_in_env(exec->env, "PWD", path);
	if (to_free || ft_strnstr(pwd, path, ft_strlen(path)))
		gc_free(path);
}
