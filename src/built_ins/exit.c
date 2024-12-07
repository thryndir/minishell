/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thryndir <thryndir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:51:27 by lgalloux          #+#    #+#             */
/*   Updated: 2024/12/07 17:12:50 by thryndir         ###   ########.fr       */
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

void	exit_builtin(t_command *cmd, t_exec *exec)
{
	(void)exec;
	if (cmd->argv[2] && is_only_digit(cmd->argv[1]))
	{
		print_error("minishell: exit", "too many arguments", 1);
		return ;
	}
	else if (!cmd->argv[1])
	{
		exit(g_exit_code);
	}
	else if (is_only_digit(cmd->argv[1]))
	{
		exit(ft_atoull(cmd->argv[1]));
	}
	else
	{
		print_error("minishell: exit numeric argument required"
			, cmd->argv[1], 2);
		exit (g_exit_code);
	}
}
