/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_manage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 20:13:05 by lgalloux          #+#    #+#             */
/*   Updated: 2024/11/20 12:02:20 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

int	lst_size(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		env = env->next;
		i++;
	}
	return (i);
}

void	free_redir(t_redir *redir)
{
	t_redir	*temp;
	t_redir	*current;

	current = redir;
	while (current)
	{
		temp = current->next;
		gc_free(current->file);
		gc_free(current);
		current = temp;
	}
}

/**
 * @brief this function free every node of cmd except if cmd isn't `NULL` and
 * free exec
 * 
 * @param exec a pointer to the exec struct
 * @param to_keep a pointer of the node cmd you don't want to free
 */
void	free_cmd_exec(t_exec *exec, t_command *to_keep)
{
	t_command	*tmp;
	t_command	*current;

	current = exec->cmd;
	while (current)
	{
		tmp = current->next;
		if (current != to_keep)
		{
			gc_tab_free(current->argv);
			gc_free(current->path);
			free_redir(current->redirections);
			gc_free(current);
			current = tmp;
		}
		current = tmp;
	}
	free_lst(exec->pid);
	gc_free(exec);
}

void	free_env(t_env *env)
{
	t_env	*temp;

	while (env)
	{
		printf("test\n");
		temp = env->next;
		gc_free(env->value);
		env->value = NULL;
		gc_free(env->name);
		env->name = NULL;
		gc_free(env);
		env = temp;
	}
	env = NULL;
}
