/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thryndir <thryndir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 18:48:01 by thryndir          #+#    #+#             */
/*   Updated: 2024/10/18 17:05:52 by thryndir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int env_builtin(t_pipex *pipex)
{
	t_env *current = pipex->env;
	
	while (current != NULL)
	{
		if (current->name && current->value)
		{
			ft_dprintf(2, "%s=", current->name);
			ft_dprintf(2, "%s\n", current->value);
		}
		else
		{
			ft_dprintf(2, "Invalid environment variable\n");
		}
		current = current->next;
	}

	return(0);
}
