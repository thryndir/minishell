/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgerbaul <jgerbaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:49:57 by lgalloux          #+#    #+#             */
/*   Updated: 2024/12/10 13:45:08 by jgerbaul         ###   ########.fr       */
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
		while (cmd->argv[i] && !ft_strcmp(cmd->argv[i], "-n"))
			i++;
		j = 0;
	}
	while (cmd->argv[i])
	{
		printf("%s ", cmd->argv[i++]);
		if (cmd->argv[i] && cmd->argv[i + 1] == NULL)
			printf("%s", cmd->argv[i++]);
	}
	if (j)
		printf("\n");
	g_exit_code = 0;
}
