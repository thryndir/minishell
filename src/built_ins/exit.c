/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:51:27 by lgalloux          #+#    #+#             */
/*   Updated: 2024/12/10 16:32:06 by lgalloux         ###   ########.fr       */
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
	long	arg;

	(void)exec;
	arg = ft_atoull(cmd->argv[1]);
	if (cmd->argc > 2 && is_only_digit(cmd->argv[1]))
	{
		print_error("minishell: exit", "too many arguments", 1);
		return ;
	}
	else if (!cmd->argv[1])
	{
		gc_free_all();
		exit(g_exit_code);
	}
	else if (is_only_digit(cmd->argv[1]))
	{
		gc_free_all();
		exit(arg);
	}
	else
	{
		print_error("minishell: exit: numeric arg required", cmd->argv[1], 2);
		gc_free_all();
		exit (g_exit_code);
	}
}
