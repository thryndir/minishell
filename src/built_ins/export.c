/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 18:48:44 by thryndir          #+#    #+#             */
/*   Updated: 2024/10/08 18:04:47 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sort_env(t_env **env)
{
	t_env	**current;
	t_env	*last;
	t_env	*temp;
	
	last = NULL;
	while (*env != last)
	{
		current = env;
		while ((*current)->next != last)
		{
			if (ft_strcmp((*current)->name, (*current)->next->name) > 0)
			{
				temp = (*current)->next;
				if (temp->next)
					temp->next->previous = *current;
				temp->previous = (*current)->previous;
				(*current)->previous = temp;
				(*current)->next = temp->next;
				temp->next = *current;
				(*current) = temp;
			}
			current = &(*current)->next;
		}
		last = *current;
	}
}

t_env	*env_copy(t_env *env)
{
	t_env	*current;
	t_env	*new;

	current = env;
	new = ft_envnew(ft_strsjoin(3, current->name, "=", current->value));
	current = current->next;
	while (current)
	{
		ft_envadd_back(&new, ft_envnew(ft_strsjoin(3, current->name, "=",
		current->value)));
		current = current->next;
	}
	return (new);
}

int	export_builtin(t_pipex *pipex)
{
	t_env	*copy;
	t_env	*temp;

	copy = env_copy(pipex->env);
	if (pipex->cmds[1] == NULL)
	{
		sort_env(&copy);
		print_lst(copy);
	}
	else
	{
		temp = ft_envnew(pipex->cmds[1]);
		add_in_env(pipex->env, temp->name, temp->value);
	}
	del_env(copy);
	return (0);
}