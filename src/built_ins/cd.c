/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thryndir <thryndir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 18:44:08 by thryndir          #+#    #+#             */
/*   Updated: 2024/10/18 18:13:25 by thryndir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int cd_builtin(t_pipex *pipex)
{
	char 	*path;
	int		to_free;

	to_free = 0;
	if (pipex->cmds[1] && 
	(pipex->cmds[1][0] == '~' || !ft_strncmp("/home", pipex->cmds[1], 5)))
		path = pipex->cmds[1];
	else
	{
		path = ft_strsjoin(3, get_value(pipex->env, "PWD"), "/", pipex->cmds[1]);
		to_free = 1;
	}
	chdir(pipex->cmds[1]);
	add_in_env(pipex->env, "PWD", path);
	if (to_free)
		free(path);
	return (0);
}
