/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 18:48:01 by thryndir          #+#    #+#             */
/*   Updated: 2024/09/23 12:24:05 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int env_builtin(t_pipex pipex)
{
	int	i;

	i = 0;
	while (pipex.env[i])
	{
		ft_dprintf(2, "%s", pipex.env[i]);
		i++;
	}
	exit(0);
}