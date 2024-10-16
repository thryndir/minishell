/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 18:48:29 by thryndir          #+#    #+#             */
/*   Updated: 2024/10/16 17:00:34 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_only_digit(char *str)
{
	int	i;
	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int exit_builtin(t_pipex *pipex)
{
	if (pipex->cmds[2])
	{
		ft_printf("minishell: exit: too many arguments");
		return (1);
	}
	else if (!pipex->cmds[1])
		exit(0);
	else if (is_only_digit(pipex->cmds[1]))
		exit(ft_atoull(pipex->cmds[1]));
	else
	{
		ft_printf("minishell: exit: %s: numeric argument required",
		pipex->cmds[1]);
		exit (2);
	}
}