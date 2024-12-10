/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:03:06 by lgalloux          #+#    #+#             */
/*   Updated: 2023/10/24 15:49:56 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int test)
{
	if ((test >= 'A' && test <= 'Z') || (test >= 'a' && test <= 'z'))
		return (1);
	return (0);
}

/*int	main(void)
{
	char c = 'a';
	printf("%d\n", isalpha(c));
	printf("%d\n", ft_isalpha(c));
}*/