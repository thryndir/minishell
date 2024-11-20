/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:50:04 by lgalloux          #+#    #+#             */
/*   Updated: 2024/11/20 11:51:07 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

int	env_builtin(t_command *cmd, t_exec *exec)
{
	t_env	*current;

	(void)cmd;
	current = exec->env;
	while (current != NULL)
	{
		if (current->name && current->value)
			printf("%s=%s\n", current->name, current->value);
		else
			dprintf(2, "Invalid environment variable\n");
		current = current->next;
	}
	return (0);
}
