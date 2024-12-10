/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:49:45 by lgalloux          #+#    #+#             */
/*   Updated: 2024/12/10 15:57:14 by lgalloux         ###   ########.fr       */
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

void	cd_builtin(t_command *cmd, t_exec *exec)
{
	char	*pwd;

	if (cmd->argc > 2)
	{
		print_error("cd", "too many arguments", 1);
		return ;
	}
	if (cmd->argc == 1)
	{
		pwd = get_value(exec->env, "HOME");
		if (verif_dir(pwd))
			return ;
	}
	else
	{
		if (verif_dir(cmd->argv[1]))
			return ;
		pwd = getcwd(NULL, 0);
	} 
	add_in_env(exec->env, "OLDPWD", get_value(exec->env, "PWD"));
	add_in_env(exec->env, "PWD", pwd);
	if (ft_strcmp(pwd, get_value(exec->env, "HOME")))
		free(pwd);
	g_exit_code = 0;
}
