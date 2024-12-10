/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 00:25:09 by lgalloux          #+#    #+#             */
/*   Updated: 2024/05/29 23:36:00 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *first, const char *second)
{
	size_t	i;

	if (first == NULL || second == NULL)
		return (0);
	i = 0;
	while (first[i] == second[i] && first[i] != '\0')
		i++;
	return ((unsigned char)(first[i]) - (unsigned char)(second[i]));
}
