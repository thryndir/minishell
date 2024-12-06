/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:49:57 by lgalloux          #+#    #+#             */
/*   Updated: 2024/12/06 14:48:39 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"
#include "parsing.h"

void	echo_builtin(t_command *cmd, t_exec *exec)
{
	int		i;
	int		j;

	i = 1;
	j = 2;
	(void)exec;
	if (cmd->argv[i] && !ft_strncmp(cmd->argv[i], "-n", 2))
	{
		while (cmd->argv[1][j] && !ft_strncmp(&cmd->argv[1][j], "n", 1))
			j++;
		if (j == (int)ft_strlen(cmd->argv[1]))
		{
			j = 0;
			i = 2;
		}
	}
	while (cmd->argv[i])
	{
		printf("%s ", cmd->argv[i++]);
		if (cmd->argv[i] && cmd->argv[i + 1] == NULL)
			printf("%s", cmd->argv[i++]);
	}
	if (j)
		printf("\n");
}
