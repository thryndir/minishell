/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:02:36 by lgalloux          #+#    #+#             */
/*   Updated: 2024/12/10 17:35:32 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

t_env	*ft_envlast(t_env *env)
{
	if (env == NULL)
		return (NULL);
	while (env->next != NULL)
	{
		env = env->next;
	}
	return (env);
}

int	pos_in_str(char *str, char to_search)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != to_search)
		i++;
	if (str[i] == to_search)
		return (i);
	return (i);
}

int	name_and_value(char *var, t_env *env)
{
	int	i;
	int	j;
	int	pos;

	i = 0;
	j = 0;
	pos = pos_in_str(var, '=');
	env->name = ft_calloc(pos + 1, sizeof(char));
	if (!env->name)
		return (1);
	env->value = ft_calloc(ft_strlen(var) - pos, sizeof(char));
	if (!env->value)
		return (1);
	while (var[i] && var[i] != '=')
	{
		env->name[i] = var[i];
		i++;
	}
	while (var[++i])
	{
		env->value[j] = var[i];
		j++;
	}
	return (0);
}

t_env	*ft_envnew(char *var)
{
	t_env	*env;

	env = gc_malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	name_and_value(var, env);
	env->next = NULL;
	return (env);
}

int	env_init(char **envp, t_exec *exec)
{
	int		i;
	t_env	*new;

	if (!envp)
	{
		exec->env = NULL;
		return (0);
	}
	exec->env = ft_envnew(envp[0]);
	if (!exec->env)
		return (1);
	i = 1;
	while (envp[i])
	{
		new = ft_envnew(envp[i]);
		if (!new)
			return (1);
		ft_envadd_back(&(exec->env), new);
		i++;
	}
	return (0);
}
