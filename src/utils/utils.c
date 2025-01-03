/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:59:30 by lgalloux          #+#    #+#             */
/*   Updated: 2024/12/10 17:14:49 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

int	read_or_write(int read_or_write, t_redir *redir)
{
	int	fd;
	int	flag;

	fd = -1;
	flag = O_TRUNC;
	if (redir->type == REDIR_HEREDOC || redir->type == REDIR_APPEND)
		flag = O_APPEND;
	if (read_or_write == READ)
		fd = open(redir->file, O_RDONLY);
	else
		fd = open(redir->file, O_WRONLY | O_CREAT | flag, 0644);
	return (fd);
}

void	double_array_free(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		gc_free(strs[i]);
		i++;
	}
	gc_free(strs);
}

void	free_lst(t_list *lst)
{
	t_list	*temp;

	while (lst)
	{
		temp = lst->next;
		gc_free(lst);
		lst = temp;
	}
}
