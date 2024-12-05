/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgerbaul <jgerbaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:49:57 by lgalloux          #+#    #+#             */
/*   Updated: 2024/12/05 02:01:53 by jgerbaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"
#include "parsing.h"

int	echo_builtin(t_command *cmd, t_exec *exec)
{
	int		i;
	bool	newline;

	i = 1;
	(void)exec;
	newline = 1;
	if (cmd->argv[i] && !ft_strcmp(cmd->argv[i], "-n"))
	{
		newline = 0;
		i = 2;
		while (!ft_strcmp(cmd->argv[i], "-n"))
			i++;
	}
	while (cmd->argv[i])
	{
		printf("%s ", cmd->argv[i++]);
		if (cmd->argv[i] && cmd->argv[i + 1] == NULL)
			printf("%s", cmd->argv[i++]);
	}
	if (newline)
		printf("\n");
	return (0);
}
