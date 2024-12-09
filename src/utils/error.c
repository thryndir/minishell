/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thryndir <thryndir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:59:57 by lgalloux          #+#    #+#             */
/*   Updated: 2024/12/09 16:15:59 by thryndir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

void	print_error(char *msg, char *detail, int exit_code)
{
	if (detail)
		dprintf(STDERR_FILENO, "%s: %s\n", msg, detail);
	else
		dprintf(STDERR_FILENO, "%s\n", msg);
	g_exit_code = exit_code;
}

void	hold_on(t_list *lst)
{
	waitpid(lst->data, &g_exit_code, 0);
	g_exit_code = WEXITSTATUS(g_exit_code);
	// dprintf(1, "la var globale vaut : %d apres avoir recup le status\n", g_exit_code);
	lst = lst->next;
	while (lst)
	{
		waitpid(lst->data, NULL, 0);
		lst = lst->next;
	}
}
