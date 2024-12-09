/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minisplit_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgerbaul <jgerbaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:54:00 by jgerbaul          #+#    #+#             */
/*   Updated: 2024/12/09 16:54:25 by jgerbaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*extract_quoted_word(const char *str, int *i, int len)
{
	int		k;
	char	*word;
	int		simple_q;
	int		double_q;

	k = 0;
	simple_q = 0;
	double_q = 0;
	word = (char *)gc_malloc((len + 1) * sizeof(char));
	if (word == NULL)
		return (NULL);
	while (str[*i])
	{
		quote_count(str[*i], &simple_q, &double_q);
		if (!(simple_q % 2) && !(double_q % 2)
			&& (is_symbol(str[*i]) || ft_isspace(str[*i])))
			break ;
		word[k++] = str[(*i)++];
	}
	word[k] = '\0';
	return (word);
}
