/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_token_swapper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgerbaul <jgerbaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 22:58:43 by jgerbaul          #+#    #+#             */
/*   Updated: 2024/11/29 23:35:37 by jgerbaul         ###   ########.fr       */
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

	if (*arg && ft_strchr(*arg, '$'))
	{
		expanded = swap_vars(*arg, env);
		if (expanded)
		{
			gc_free(*arg);
			*arg = expanded;
		}
	}
}

void	loop_env_swapper(t_command *cmd, t_env *env)
{
	int	i;

	i = 0;
	if (!cmd || !cmd->argv)
		return ;
	while (i < cmd->argc)
	{
		swap_arg(&cmd->argv[i], env);
		i++;
	}
}
