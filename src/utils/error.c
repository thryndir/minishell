/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:59:57 by lgalloux          #+#    #+#             */
/*   Updated: 2024/11/20 11:59:57 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

void	ft_error(char *message, int which, int status)
{
	if (which == 0)
		dprintf(2, "%s\n", message);
	if (which == 1 && errno)
		dprintf(2, "%s: %s\n", message, strerror(errno));
	gc_free_all();
	exit(status);
}

void	return_code(t_exec *exec)
{
	if (WIFEXITED(exec->status))
	{
		gc_free_all();
		exit(exec->status);
	}
}

void	hold_on(t_list *lst, int *status)
{
	(void)status;
	waitpid(lst->data, status, 0);
	lst = lst->next;
	while (lst)
	{
		waitpid(lst->data, NULL, 0);
		lst = lst->next;
	}
}
