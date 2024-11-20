/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:51:27 by lgalloux          #+#    #+#             */
/*   Updated: 2024/11/20 11:51:27 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

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

int	exit_builtin(t_command *cmd, t_exec *exec)
{
	(void)exec;
	if (cmd->argv[2])
	{
		dprintf(2, "minishell: exit: too many arguments");
		return (1);
	}
	else if (!cmd->argv[1])
	{
		exit(0);
	}
	else if (is_only_digit(cmd->argv[1]))
	{
		exit(ft_atoull(cmd->argv[1]));
	}
	else
	{
		dprintf(2, "minishell: exit: %s: numeric argument required",
			cmd->argv[1]);
		exit (2);
	}
}
