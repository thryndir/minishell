/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gcmalloc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgerbaul <jgerbaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 02:08:59 by jgerbaul          #+#    #+#             */
/*   Updated: 2024/11/05 00:40:54 by jgerbaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GCMALLOC_H
# define GCMALLOC_H

# include <stdlib.h>
# include <stdio.h>

typedef struct s_alloc_ptr
{
	void				*addr;
	size_t				size;
	struct s_alloc_ptr	*next;
}	t_alloc_ptr;

void		lst_add_back(t_alloc_ptr *lst, t_alloc_ptr *new);
void		free_elem(t_alloc_ptr *elem);
int			gc_length(int code);
void		gc_free_all(void);
void		gc_free(void *addr);
void		gc_tab_free(char **addr);

t_alloc_ptr	*new_node(size_t size);
t_alloc_ptr	*remove_address(int index, t_alloc_ptr *lst);
t_alloc_ptr	*addr_save(t_alloc_ptr *ptr, int code);
void		*gc_malloc(size_t size);

#endif