/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_token_swapper_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgerbaul <jgerbaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 22:32:58 by jgerbaul          #+#    #+#             */
/*   Updated: 2024/11/29 22:54:44 by jgerbaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"
#include "parsing.h"

char	*env_substr(char const *str, unsigned int start, size_t sublen)
{
	size_t		j;
	size_t		size;
	char		*substr;

	j = 0;
	size = 0;
	if (str == NULL)
		return (NULL);
	if (start >= ft_strlen(str))
		return (mini_strdup(""));
	while (str[start + size])
		size++;
	if (size > sublen)
		size = sublen;
	substr = gc_malloc((size + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	while (j < size && str[start])
		substr[j++] = str[start++];
	substr[j] = '\0';
	return (substr);
}

int	get_var_name_len(const char *str)
{
	int	i;

	i = 1;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (i);
}

void	copy_var_value(char *result, int *j, char *var_value)
{
	if (var_value)
	{
		ft_strlcpy(result + *j, var_value, ft_strlen(var_value) + 1);
		*j += ft_strlen(var_value);
	}
}

char	*get_var_value(char *str, int *i, t_env *env)
{
	char	*var_name;
	char	*var_value;
	int		var_len;

	var_len = get_var_name_len(str + *i);
	var_name = env_substr(str, *i + 1, var_len - 1);
	var_value = get_value(env, var_name);
	gc_free(var_name);
	*i += var_len;
	return (var_value);
}

void	handle_var_expansion(char *str, t_expansion *exp)
{
	char	*var_value;

	var_value = get_var_value(str, exp->i, exp->env);
	copy_var_value(exp->result, exp->j, var_value);
}
