/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_remove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgerbaul <jgerbaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 00:02:12 by jgerbaul          #+#    #+#             */
/*   Updated: 2024/12/08 19:26:15 by jgerbaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	should_toggle_quote(char current,
			char quote_type, int in_other_quote)
{
	if (current == quote_type && !in_other_quote)
		return (1);
	return (0);
}

static void	copy_char(char current, char *new_str, int *j)
{
	new_str[*j] = current;
	*j += 1;
}

static void	process_string(char *str, char *new_str)
{
	int	i;
	int	j;
	int	in_double;
	int	in_single;

	i = 0;
	j = 0;
	in_double = 0;
	in_single = 0;
	while (str[i])
	{
		if (should_toggle_quote(str[i], '\"', in_single))
			in_double = !in_double;
		else if (should_toggle_quote(str[i], '\'', in_double))
			in_single = !in_single;
		else
			copy_char(str[i], new_str, &j);
		i++;
	}
	new_str[j] = '\0';
}

char	*remove_quotes_from_string(char *str)
{
	char	*new_str;
	int		len;

	len = ft_strlen(str);
	new_str = malloc(len + 1);
	if (!new_str)
		return (NULL);
	process_string(str, new_str);
	return (new_str);
}
