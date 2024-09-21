/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thryndir <thryndir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:28:55 by lgalloux          #+#    #+#             */
/*   Updated: 2024/09/21 18:35:25 by thryndir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo_builtin(char **cmds)
{
	int		start;
	int		i;
	bool	newline;

	start = 0;
	i = 0;
	newline = 1;
	while (cmds[0][start] && cmds[0][start] != '-')
		start++;
	if (cmds[0][start + 1] == 'n')
	{
		newline = 0;
		i = 1;
	}
	while (cmds[i])
	{
		ft_printf("%s ", cmds[i++]);
		if (cmds[i + 1] == NULL)
			ft_printf("%s", cmds[i++]);
	}
	if (newline)
		write(1, "\n", 1);
	exit(0);
}
