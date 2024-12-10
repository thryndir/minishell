/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:58:08 by lgalloux          #+#    #+#             */
/*   Updated: 2024/05/16 05:23:11 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(int data)
{
	t_list	*stack;

	stack = gc_malloc(sizeof(t_list));
	if (!stack)
		return (NULL);
	stack->data = data;
	stack->next = NULL;
	return (stack);
}
