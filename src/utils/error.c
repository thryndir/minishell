/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:59:57 by lgalloux          #+#    #+#             */
/*   Updated: 2024/12/11 10:24:59 by lgalloux         ###   ########.fr       */
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

void	error_and_quit(char *msg, char *detail, int exit_code)
{
	print_error(msg, detail, exit_code);
	gc_free_all();
	exit(g_exit_code);
}

void	hold_on(t_list *lst)
{
	waitpid(lst->data, &g_exit_code, 0);
	g_exit_code = WEXITSTATUS(g_exit_code);
	lst = lst->next;
	while (lst)
	{
		waitpid(lst->data, NULL, 0);
		lst = lst->next;
	}
}
