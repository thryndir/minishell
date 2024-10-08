/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 18:49:21 by thryndir          #+#    #+#             */
/*   Updated: 2024/10/08 14:27:54 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_lst(t_env *env)
{
	t_env *curr;
	
	curr = env;
	while (curr)
	{
		ft_dprintf(2, "%s\n", curr->name);
		curr = curr->next;
	}
}

int	ft_strscmp(char **cmds, char *name, int cmd_nbr)
{
	int	i;

	i = 0;
	while (cmds && i < cmd_nbr)
	{
		if (!ft_strcmp(cmds[i], name))
			return(0);
		i++;
	}
	return (1);
}

int unset_builtin(t_pipex *pipex)
{
	t_env *next;
	t_env *curr;

	curr = pipex->env;
	while (curr)
	{
		next = curr->next;
		if (!ft_strscmp(pipex->cmds, curr->name, pipex->cmd_nbr))
			del_in_env(pipex->env, curr);
		curr = next;
	}
	exit(0);
}
