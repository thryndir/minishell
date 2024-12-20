/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:51:33 by lgalloux          #+#    #+#             */
/*   Updated: 2024/12/10 17:22:53 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

void	print_lst(t_env *env)
{
	t_env	*curr;
	char	*var;

	curr = env;
	while (curr)
	{
		var = ft_strsjoin(3, curr->name, "=", curr->value);
		printf("%s\n", var);
		gc_free(var);
		curr = curr->next;
	}
}

void	sort_env(t_env *env)
{
	t_env	*i;
	t_env	*j;
	char	*tmp;

	i = env;
	while (i)
	{
		j = i->next;
		while (j)
		{
			if (ft_strcmp(i->name, j->name) > 0)
			{
				tmp = i->name;
				i->name = j->name;
				j->name = tmp;
				tmp = i->value;
				i->value = j->value;
				j->value = tmp;
			}
			j = j->next;
		}
		i = i->next;
	}
}

t_env	*env_copy(t_env *env)
{
	t_env	*current;
	t_env	*new;
	char	*var;

	current = env;
	var = ft_strsjoin(3, current->name, "=", current->value);
	new = ft_envnew(var);
	gc_free(var);
	current = current->next;
	while (current)
	{
		var = ft_strsjoin(3, current->name, "=", current->value);
		ft_envadd_back(&new, ft_envnew(var));
		gc_free(var);
		current = current->next;
	}
	return (new);
}

void	export_builtin(t_command *cmd, t_exec *exec)
{
	t_env	*copy;
	t_env	*temp;
	int		i;

	temp = NULL;
	copy = env_copy(exec->env);
	i = 1;
	if (cmd->argc <= 1)
	{
		sort_env(copy);
		print_lst(copy);
	}
	else
	{
		while (cmd->argv[i])
		{
			temp = ft_envnew(cmd->argv[i]);
			add_in_env(exec->env, temp->name, temp->value);
			i++;
		}
	}
	del_env(temp);
	del_env(copy);
	g_exit_code = 0;
}
