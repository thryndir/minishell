/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgerbaul <jgerbaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:49:57 by lgalloux          #+#    #+#             */
/*   Updated: 2024/12/05 00:22:18 by jgerbaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

int	is_only_c(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != c)
			return (0);
		i++;
	}
	return (1);
}

int	echo_builtin(t_command *cmd, t_exec *exec)
{
	int		i;
	bool	newline;

	i = 1;
	(void)exec;
	newline = 1;
	if (cmd->argv[i] && is_only_c(cmd->argv[i] + 1, 'n'))
	{
		newline = 0;
		i = 2;
		while (is_only_c(cmd->argv[i] + 1, 'n'))
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
