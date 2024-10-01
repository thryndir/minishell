/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 18:49:21 by thryndir          #+#    #+#             */
/*   Updated: 2024/10/01 16:04:19 by lgalloux         ###   ########.fr       */
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

int	ft_strscmp(char **strs, char *str)
{
	int	i;

	i = 0;
	while (strs)
	{
		if (!ft_strcmp(strs[i], str))
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
		if (!ft_strscmp(pipex->cmds, curr->name))
		{
			if (curr->next && curr->previous)
			{
				next->previous = curr->previous;
				curr->previous->next = next;
			}
			free(curr->name);
			free(curr->value);
			free(curr);
			curr = NULL;
		}
		curr = next;
		print_lst(pipex->env);
	}
	print_lst(pipex->env);
	exit(0);
}
