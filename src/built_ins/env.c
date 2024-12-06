/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:50:04 by lgalloux          #+#    #+#             */
/*   Updated: 2024/12/06 17:24:12 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

void	env_builtin(t_command *cmd, t_exec *exec)
{
	t_env	*current;

	(void)cmd;
	current = exec->env;
	while (current != NULL)
	{
		if (current->name && current->value)
			printf("%s=%s\n", current->name, current->value);
		current = current->next;
	}
}
