/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 15:51:27 by lgalloux          #+#    #+#             */
/*   Updated: 2023/10/24 15:51:29 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int test)
{
	if (test >= '0' && test <= '9')
		return (1);
	else if ((test >= 'a' && test <= 'z') || (test >= 'A' && test <= 'Z'))
		return (1);
	return (0);
}

/*int	main(void)
{
	int test = '@';
	printf("%d\n%d\n", isalnum(test), ft_isalnum(test));
}*/