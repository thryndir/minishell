/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_token_swapper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgerbaul <jgerbaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 22:58:43 by jgerbaul          #+#    #+#             */
/*   Updated: 2024/12/10 13:45:23 by jgerbaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"
#include "parsing.h"

int	get_var_len(char *str, int *i, t_env *env)
{
	char	*var_name;
	char	*var_value;
	int		var_len;
	int		len;

	len = 0;
	var_len = get_var_name_len(str + *i);
	var_name = env_substr(str, *i + 1, var_len - 1);
	var_value = get_value(env, var_name);
	if (var_value)
		len = ft_strlen(var_value);
	else
		len = 0;
	gc_free(var_name);
	*i += var_len;
	return (len);
}

int	get_expanded_len(char *str, t_env *env)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && str[i + 1] != ' ')
			len += get_var_len(str, &i, env);
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

char	*swap_vars(char *str, t_env *env)
{
	t_expansion	exp;
	int			i;
	int			j;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	exp.result = gc_malloc(sizeof(char) * (get_expanded_len(str, env) + 1));
	if (!exp.result)
		return (NULL);
	exp.env = env;
	exp.i = &i;
	exp.j = &j;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && str[i + 1] != ' ')
			handle_var_expansion(str, &exp);
		else
			exp.result[j++] = str[i++];
	}
	exp.result[j] = '\0';
	return (exp.result);
}

void	swap_arg(char **arg, t_env *env)
{
	char	*expanded;

	if (*arg && found_dollar_qm(*arg)
		&& ((*arg[0] != '\'') || !ft_strcmp(*arg, "\'\'$?\'\'")))
	{
		expanded = mini_itoa(g_exit_code);
		if (expanded)
		{
			gc_free(*arg);
			*arg = expanded;
		}
	}
	else if (*arg && ft_strchr(*arg, '$')
		&& ((*arg[0] != '\'') || !ft_strncmp(*arg, "\'\'", 2)))
	{
		expanded = swap_vars(*arg, env);
		if (expanded)
		{
			gc_free(*arg);
			*arg = expanded;
		}
	}
}

void	loop_env_swapper(char **splitted, t_env *env)
{
	int	i;

	i = 0;
	if (!splitted)
		return ;
	while (splitted[i])
	{
		swap_arg(&splitted[i], env);
		i++;
	}
}
