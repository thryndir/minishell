/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_malloc_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgerbaul <jgerbaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 02:11:14 by jgerbaul          #+#    #+#             */
/*   Updated: 2024/11/05 00:40:58 by jgerbaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gcmalloc.h"

/** 
 * This function add a new allocation at the end of
 * the current linked list
 */
void	lst_add_back(t_alloc_ptr *lst, t_alloc_ptr *new)
{
	t_alloc_ptr	*tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
	}
	tmp->next = new;
}

/**
 * This function free the struct *elem
 */
void	free_elem(t_alloc_ptr *elem)
{
	if (elem)
	{
		free(elem->addr);
		free(elem);
	}
}

/**
 * This function manage the index of the gc
 * 0 = get current index
 * 1 = increment index
 * 2 = set index to 0
 * 3 = decrement index
 */
int	gc_length(int code)
{
	int			index;
	static int	length;

	index = length;
	if (code == 1)
		length++;
	else if (code == 2)
		length = 0;
	else if (code == 3)
		length--;
	return (index);
}

/**
 * This function free every memory that was allocated
 */
void	gc_free_all(void)
{
	t_alloc_ptr	*lst;
	t_alloc_ptr	*tmp;

	lst = addr_save(NULL, 1);
	while (lst)
	{
		tmp = lst->next;
		free(lst->addr);
		free(lst);
		lst = tmp;
	}
	gc_length(2);
}

/**
 * This function free a node
 */
void	gc_free(void *addr)
{
	int			index;
	t_alloc_ptr	*lst;

	index = 0;
	lst = addr_save(NULL, 1);
	while (lst)
	{
		if (lst->addr == addr)
			break ;
		lst = lst->next;
		index++;
	}
	if (!lst)
		return ;
	lst = remove_address(index, addr_save(NULL, 1));
	addr_save(lst, 0);
	gc_length(3);
}
