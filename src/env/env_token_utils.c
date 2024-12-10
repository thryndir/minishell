/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_token_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgerbaul <jgerbaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 01:22:59 by jgerbaul          #+#    #+#             */
/*   Updated: 2024/12/10 13:45:34 by jgerbaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"
#include "parsing.h"

char	*mini_nbr_is_negative(char *str, int nbr2, int len)
{
	str[0] = '-';
	nbr2 *= -1;
	while (len > 0)
	{
		str[len] = nbr2 % 10 + '0';
		nbr2 = nbr2 / 10;
		len--;
	}
	return (str);
}

char	*mini_nbr_is_positive(char *str, int nbr2, int len)
{
	while (len > -1)
	{
		str[len] = nbr2 % 10 + '0';
		nbr2 = nbr2 / 10;
		len--;
	}
	return (str);
}

int	mini_nbr_count(int nbr)
{
	int	len;

	len = 0;
	if (nbr < 0)
	{
		nbr *= -1;
		len = 1;
	}
	else
		len = 0;
	while (nbr >= 10)
	{
		nbr = nbr / 10;
		len++;
	}
	return (len);
}

char	*mini_itoa(int nbr)
{
	char	*str;
	int		len;

	if (nbr == -2147483648)
		return (ft_strdup("-2147483648"));
	len = mini_nbr_count(nbr);
	str = gc_malloc(len + 2 * sizeof(char));
	if (str == NULL)
		return (NULL);
	if (nbr < 0)
		str = mini_nbr_is_negative(str, nbr, len);
	else
		str = mini_nbr_is_positive(str, nbr, len);
	str[len + 1] = '\0';
	return (str);
}

int	found_dollar_qm(const char *string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (string[i] == '$' && (string[i + 1]) == '?')
			return (1);
		i++;
	}
	return (0);
}
