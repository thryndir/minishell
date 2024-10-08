/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 18:48:01 by thryndir          #+#    #+#             */
/*   Updated: 2024/10/08 14:27:41 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int env_builtin(t_pipex *pipex)
{
	while (pipex->env)
	{
		ft_dprintf(2, "%s", pipex->env->name);
		write(2, "=", 1);
		ft_dprintf(2, "%s", pipex->env->value);
		write(2, "\n", 1);
		pipex->env = pipex->env->next;
	}
	exit(0);
}