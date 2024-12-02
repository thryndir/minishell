/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgerbaul <jgerbaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:49:45 by lgalloux          #+#    #+#             */
/*   Updated: 2024/12/03 00:51:46 by jgerbaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

int	is_forbidden_symbol(char *str)
{
	if (!ft_strcmp(str, ".."))
		return (1);
	else if (!ft_strcmp(str, "~"))
		return (1);
	else if (!ft_strcmp(str, "-"))
		return (1);
	else
		return (0);
}

int	cd_builtin(t_command *cmd, t_exec *exec)
{
	char	*path;
	int		to_free;

	to_free = 0;
	if (chdir(cmd->argv[1]) != 0 || is_forbidden_symbol(cmd->argv[1]))
	{
		printf("cd: No such file or directory\n");
		return (1);
	}
	if (cmd->argv[1] && (cmd->argv[1][0] == '~'
		|| !ft_strncmp("/home", cmd->argv[1], 5)))
		path = cmd->argv[1];
	else
	{
		path = ft_strsjoin(3, get_value(exec->env, "PWD"),
				"/", cmd->argv[1]);
		to_free = 1;
	}
	add_in_env(exec->env, "PWD", path);
	if (to_free)
		gc_free(path);
	return (0);
}
