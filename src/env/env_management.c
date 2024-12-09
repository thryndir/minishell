/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thryndir <thryndir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:02:39 by lgalloux          #+#    #+#             */
/*   Updated: 2024/12/09 15:39:25 by thryndir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

void	ft_envadd_back(t_env **env, t_env *new)
{
	t_env	*temp;

	if (env == NULL)
		*env = new;
	else
	{
		temp = ft_envlast(*env);
		temp->next = new;
	}
}

void	del_env(t_env *env)
{
	t_env	*temp;

	while (env)
	{
		temp = env->next;
		gc_free(env->name);
		gc_free(env->value);
		gc_free(env);
		env = temp;
	}
}

void	del_in_env(t_env **env, t_env *to_delete)
{
	t_env	*current;

	current = *env;
	while (current && current->next != to_delete && current != to_delete)
		current = current->next;
	if (*env == to_delete)
		*env = (*env)->next;
	else
		current->next = to_delete->next;
	gc_free(to_delete->name);
	gc_free(to_delete->value);
	gc_free(to_delete);
}

void	add_in_env(t_env *env, char *name, char *value)
{
	t_env	*current;
	char	*temp;
	char	*var;

	current = env;
	while (current)
	{
		if (!ft_strcmp(current->name, name))
		{
			temp = current->value;
			current->value = ft_strdup(value);
			gc_free(temp);
			return ;
		}
		current = current->next;
	}
	var = ft_strsjoin(3, name, "=", value);
	ft_envadd_back(&env, ft_envnew(var));
	gc_free(var);
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
