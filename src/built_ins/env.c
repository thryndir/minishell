/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thryndir <thryndir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:50:04 by lgalloux          #+#    #+#             */
/*   Updated: 2024/12/07 17:16:04 by thryndir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

void	env_builtin(t_command *cmd, t_exec *exec)
{
	t_env	*current;

	if (cmd->argc > 1)
	{
		print_error("mininshell: env", "too many arguments", 1);
		return ;
	}
	(void)cmd;
	current = exec->env;
	while (current != NULL)
	{
		if (current->name && current->value)
			printf("%s=%s\n", current->name, current->value);
		current = current->next;
	}
	g_exit_code = 0;
}
