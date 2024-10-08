/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:27:27 by lgalloux          #+#    #+#             */
/*   Updated: 2024/10/08 14:26:24 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	del_env(t_env *env)
{
	t_env *temp;

	while (env)
	{
		temp = env->next;
		free(env->name);
		free(env->value);
		free(env);
		env = temp;
	}
}

void	del_in_env(t_env *env, t_env *to_delete)
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
	char	*var;

	current = env;
	while (current)
	{
		if (!ft_strcmp(current->name, name) && ft_strcmp(current->value, value))
		{
			free(current->value);
			current->value = ft_calloc(ft_strlen(value), sizeof(char));
			ft_strlcpy(current->value, value, ft_strlen(value));
			return;
		}
		current = current->next;
	}
	var = ft_strsjoin(3, name, "=", value);
	ft_envadd_back(&env, ft_envnew(var));
}

char	*get_value(t_env *env, char *name)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (!ft_strcmp(current->name, name))
			return (current->value);
		current = current->next;
	}
	return (NULL);
}