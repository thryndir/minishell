/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:28:55 by lgalloux          #+#    #+#             */
/*   Updated: 2024/09/17 15:05:46 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// #TODO faire un exec built-ins qui prend le nom de la fonction, les args et le env

void	ft_echo(char **argv)
{
	int		start;
	int		i;
	bool	newline;

	start = 0;
	i = 0;
	newline = 1;
	while (argv[0][start] && argv[0][start] != '-')
		start++;
	if (argv[0][start + 1] == 'n')
	{
		newline = 0;
		i = 1;
	}
	while (argv[i])
	{
		ft_printf("%s ", argv[i++]);
		if (argv[i + 1] == NULL)
			ft_printf("%s", argv[i++]);
	}
	if (newline)
		write(1, "\n", 1);
	return;
}
