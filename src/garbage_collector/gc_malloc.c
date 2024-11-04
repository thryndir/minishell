/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgerbaul <jgerbaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 02:09:05 by jgerbaul          #+#    #+#             */
/*   Updated: 2024/11/05 00:40:56 by jgerbaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gcmalloc.h"

/**
 * This function create and initialize a new node
 */
t_alloc_ptr	*new_node(size_t size)
{
	t_alloc_ptr	*lst;

	lst = malloc(sizeof(t_alloc_ptr));
	if (!lst)
		return (NULL);
	lst->next = NULL;
	lst->size = size;
	lst->addr = malloc(size);
	return (lst);
}

/**
 * This function free a node using it's index
 */
t_alloc_ptr	*remove_address(int index, t_alloc_ptr *lst)
{
	t_alloc_ptr	*new_lst;
	t_alloc_ptr	*past;

	if (!index)
	{
		new_lst = lst->next;
		free_elem(lst);
		return (new_lst);
	}
	new_lst = lst;
	while (index)
	{
		past = lst;
		lst = lst->next;
		index--;
	}
	past->next = lst->next;
	free_elem(lst);
	return (new_lst);
}

/**
 * This function can create a linked list or add a
 * node to an existing linked list
 */
t_alloc_ptr	*addr_save(t_alloc_ptr *ptr, int code)
{
	static t_alloc_ptr	*lst;

	if (!code)
		lst = ptr;
	else if (ptr)
		lst_add_back(lst, ptr);
	return (lst);
}

/**
 * This function free an array of node
 */
void	gc_tab_free(char **addr)
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

/**
 * This function allocation memory using the size (in byte)
 * and track it for a better deletion
 */
void	*gc_malloc(size_t size)
{
	t_alloc_ptr	*lst;

	lst = new_node(size);
	if (!lst)
		return (NULL);
	if (gc_length(1) == 0)
		addr_save(lst, 0);
	else
		addr_save(lst, 1);
	return (lst->addr);
}
