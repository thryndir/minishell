/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thryndir <thryndir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:51:45 by lgalloux          #+#    #+#             */
/*   Updated: 2024/12/07 17:04:16 by thryndir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

void	print_lst(t_env *env)
{
	t_env	*curr;
	char	*var;

	curr = env;
	while (curr)
	{
		var = ft_strsjoin(3, curr->name, "=", curr->value);
		dprintf(2, "%s\n", var);
		gc_free(var);
		curr = curr->next;
	}
}

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
