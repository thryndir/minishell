/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thryndir <thryndir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:49:45 by lgalloux          #+#    #+#             */
/*   Updated: 2024/12/07 17:01:26 by thryndir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

int	verif_dir(char *args)
{
	if (chdir(args) != 0)
	{
		print_error("cd", strerror(errno), errno);
		return (errno);
	}
	return (0);
}

char *revtrim(char *str, char *to_trim)
{
	int		start;
	int		size;

	start = 0;
	size = ft_strlen(str);
	while (size >= 0)
	{
		if (!strcmp(&str[size], to_trim))
			break;
		size--;
	}
	return(ft_substr(str, start, size));
}

char *transform_symbols(char *symbol, t_exec *exec)
{
	char *result;

	result = symbol;
	if (!result || (!ft_strcmp(result, "~")))
	{
		result = ft_strdup(get_value(exec->env, "HOME"));
		return (result); //verifier ce que renvoie le parsing en cas de cd ''
	}
	else if (!ft_strcmp(result, "."))
		result = ft_strdup(get_value(exec->env, "PWD"));
	else if (!ft_strcmp(result, "-"))
		result = ft_strdup(get_value(exec->env, "OLDPWD"));
	else if (result[0] == '~')
		result = ft_strjoin(get_value(exec->env, "HOME"), &result[1]);
	if (!ft_strcmp(result, "/") || result[ft_strlen(result) - 1] == '/')
	{
		if (result != symbol)
			gc_free(result);
		result = ft_strdup(result);
		result[ft_strlen(result) - 1] = '\0';
	}
	if (result != symbol)
		result = ft_strdup(symbol);
	return (result);
}

char	*update_path(char *path, char *pwd, char *sep)
{
	char	*result;
	char	*temp;

	result = path;
	if (!ft_strcmp(path, ".."))
	{
		gc_free(path);
		result = revtrim(pwd, ft_strrchr(pwd, '/'));
		temp = result;
		if (!result || !result[0])
			result = ft_strdup("/");
		if (!ft_strcmp(result, "/"))
			gc_free(temp);
	}
	else if (ft_strncmp("/home", path, 5))
	{
		if (!ft_strcmp(pwd, "/"))
			sep = "";
		temp = path;
		result = ft_strsjoin(3, pwd, sep, path);
		gc_free(temp);
	}
	else
		result = ft_strdup(path);
	return (result);
}

void	cd_builtin(t_command *cmd, t_exec *exec)
{
	char	*path;
	char	*pwd;
	char	*sep;

	if (cmd->argc > 2)
	{
		print_error("cd", "too many arguments", 1);
		return ;
	}
	pwd = get_value(exec->env, "PWD");
	path = transform_symbols(cmd->argv[1], exec);
	add_in_env(exec->env, "OLDPWD", pwd);
	if (verif_dir(path))
		return ;
	sep = "/";
	path = update_path(path, pwd, sep);
	add_in_env(exec->env, "PWD", path);
	gc_free(path);
	g_exit_code = 0;
}
