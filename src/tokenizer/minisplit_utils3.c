/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minisplit_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgerbaul <jgerbaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 00:02:12 by jgerbaul          #+#    #+#             */
/*   Updated: 2024/12/05 00:02:26 by jgerbaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	remove_quotes_from_argv(char **argv)
{
	int		i;
	char	*new_str;
	int		len;

	i = 0;
	while (argv[i])
	{
		len = ft_strlen(argv[i]);
		if (len > 1 && is_quote(argv[i][0]) && is_quote(argv[i][len - 1]))
		{
			new_str = gc_malloc(len - 1);
			ft_strlcpy(new_str, argv[i] + 1, len - 1);
			gc_free(argv[i]);
			argv[i] = new_str;
		}
		i++;
	}
}
