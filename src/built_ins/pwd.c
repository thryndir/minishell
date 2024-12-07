/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thryndir <thryndir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:51:39 by lgalloux          #+#    #+#             */
/*   Updated: 2024/12/07 17:19:21 by thryndir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

void	pwd_builtin(t_command *cmd, t_exec *exec)
{
	if (cmd->argc > 1)
	{
		print_error("minishell: pwd", "too many arguments", 1);
		return ;
	}

	(void)cmd;
	printf("%s\n", get_value(exec->env, "PWD"));
	g_exit_code = 0;
}
