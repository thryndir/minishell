/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 18:49:05 by thryndir          #+#    #+#             */
/*   Updated: 2024/09/23 12:24:36 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int pwd_builtin(t_pipex pipex)
{
	(void)pipex;
	char *str;
	str = NULL;
	ft_dprintf(2, "%s\n", getcwd(str, 0));
	exit(0);
}