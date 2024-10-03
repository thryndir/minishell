/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strsjoin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thryndir <thryndir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 10:46:13 by thryndir          #+#    #+#             */
/*   Updated: 2024/10/03 11:55:14 by thryndir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		size_and_convert(char **strs, int str_nbr, va_list arg)
{
	int	result;
	int	i;

	i = 0;
	while (i < str_nbr)
	{
		strs[i] = va_arg(arg, char *);
		result += ft_strlen(strs[i]);
		i++;
	}
}

char 	*ft_strsjoin(int str_nbr, ...)
{
	va_list arg;
	int		total_len;
	int		i;
	char 	*result;
	char 	**strs;

	strs = (char **)malloc(str_nbr * sizeof(char *) + 1);
	i = 0;
	va_start(arg, str_nbr);
	total_len = size_and_convert(strs, str_nbr, arg);
	result = (char *)ft_calloc(sizeof(char), total_len + 1);
	ft_strlcpy(result, strs[i], total_len);
	while (i < str_nbr)
	{
		ft_strlcat(result, strs[i], total_len);
		i++;
	}
	free(strs);
}
