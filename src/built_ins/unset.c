/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 18:49:21 by thryndir          #+#    #+#             */
/*   Updated: 2024/09/23 17:47:56 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int unset_builtin(t_pipex *pipex)
{
	int	i;
	int	j;
	
	i = 0;
	j = 0;
	while (pipex->env[i])
	{
		if (!ft_strcmp(pipex->cmds[1], pipex->env[i]))
		{
			free(pipex->env[i]);
			while (pipex->env[i])
			{
				pipex->env[i] = pipex->env[i + 1];
				i++;
			}
			pipex->env[i] = NULL;
		}
		i++;
	}
	exit(0);
}
