/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:51:39 by lgalloux          #+#    #+#             */
/*   Updated: 2024/12/06 14:54:06 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

void	pwd_builtin(t_command *cmd, t_exec *exec)
{
	(void)cmd;
	printf("%s\n", get_value(exec->env, "PWD"));
}
