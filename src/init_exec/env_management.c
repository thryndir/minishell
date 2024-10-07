/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:27:27 by lgalloux          #+#    #+#             */
/*   Updated: 2024/10/02 16:57:18 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
##TODO 

void	ft_envadd_back(t_env **env, t_env *new)
{
	t_env	*temp;

	if (env == NULL)
		*env = new;
	else
	{
		temp = ft_envlast(*env);
		temp->next = new;
		new->previous = temp;
	}
}

void	del_in_env(t_env *env, t_env *to_delete, char *name)
{
	if (to_delete->next && !(to_delete->previous))
		env = env->next;
	else if (to_delete->next && to_delete->previous)
	{
		to_delete->next->previous = to_delete->previous;
		to_delete->previous->next = to_delete->next;
	}
	free(to_delete->name);
	free(to_delete->value);
	free(to_delete);
	to_delete = NULL;
}

void	add_in_env(t_env *env, char *name, char *value)
{
	t_env 	*current;
	char	*cat;

	current = env;
	while (current)
	{
		if (!ft_strcmp(current->name, name) && !ft_strcmp(current->value, value))
		{
			free(current->value);
			current->value = ft_calloc(ft_strlen(value), sizeof(char));
			ft_strlcpy(current->value, value, ft_strlen(value));
			return;
		}
		current = current->next;
	}
	cat = calloc(ft_strlen(name) + ft_strlen(value) +)
	ft_envadd_back(&env, ft_envnew())
}