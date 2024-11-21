/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:59:57 by lgalloux          #+#    #+#             */
/*   Updated: 2024/11/21 17:18:47 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

void	ft_error(char *message, int which, int status)
{
	if (which == 0 && message)
		dprintf(2, "%s\n", message);
	if (which == 1 && errno && message)
		dprintf(2, "%s: %s\n", message, strerror(errno));
	gc_free_all();
	exit(status);
}

void	hold_on(t_list *lst)
{
	waitpid(lst->data, &g_exit_code, 0);
	lst = lst->next;
	while (lst)
	{
		waitpid(lst->data, NULL, 0);
		lst = lst->next;
	}
}
