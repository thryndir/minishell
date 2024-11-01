/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strsjoin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thryndir <thryndir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 10:46:13 by thryndir          #+#    #+#             */
/*   Updated: 2024/10/22 12:06:41 by thryndir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

int	size_and_convert(char **strs, int str_nbr, va_list arg)
{
	int	result;
	int	i;

	i = 0;
	result = 0;
	while (i < str_nbr)
	{
		strs[i] = va_arg(arg, char *);
		result += ft_strlen(strs[i]);
		i++;
	}
	return (result);
}

char	*ft_strsjoin(int str_nbr, ...)
{
	va_list	arg;
	int		total_len;
	int		i;
	char	*result;
	char	**strs;

	strs = (char **)malloc(str_nbr * sizeof(char *) + 1);
	i = 0;
	va_start(arg, str_nbr);
	total_len = size_and_convert(strs, str_nbr, arg) + 1;
	result = (char *)ft_calloc(sizeof(char), total_len + 1);
	while (i < str_nbr)
	{
		ft_strlcat(result, strs[i], total_len);
		i++;
	}
	free(strs);
	return (result);
}
