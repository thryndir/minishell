/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:51:45 by lgalloux          #+#    #+#             */
/*   Updated: 2024/12/10 12:33:50 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

int	ft_strscmp(char **cmds, char *name, int cmd_nbr)
{
	int	i;

	i = 0;
	while (cmds && i < cmd_nbr)
	{
		if (!ft_strcmp(cmds[i], name))
			return (0);
		i++;
	}
	return (1);
}

void	unset_builtin(t_command *cmd, t_exec *exec)
{
	t_env	*next;
	t_env	*curr;

	curr = exec->env;
	while (curr)
	{
		next = curr->next;
		if (!ft_strscmp(cmd->argv, curr->name, cmd->argc))
			del_in_env(&(exec->env), curr);
		curr = next;
	}
	g_exit_code = 0;
}
