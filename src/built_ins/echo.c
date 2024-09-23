/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:28:55 by lgalloux          #+#    #+#             */
/*   Updated: 2024/09/23 12:23:39 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo_builtin(t_pipex pipex)
{
	int		start;
	int		i;
	bool	newline;

	start = 0;
	i = 0;
	newline = 1;
	while (pipex.cmds[0][start] && pipex.cmds[0][start] != '-')
		start++;
	if (pipex.cmds[0][start + 1] == 'n')
	{
		newline = 0;
		i = 1;
	}
	while (pipex.cmds[i])
	{
		ft_printf("%s ", pipex.cmds[i++]);
		if (pipex.cmds[i + 1] == NULL)
			ft_printf("%s", pipex.cmds[i++]);
	}
	if (newline)
		write(1, "\n", 1);
	exit(0);
}
