/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 20:18:40 by lgalloux          #+#    #+#             */
/*   Updated: 2024/12/06 11:02:59 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

char	**lst_to_array(t_env *env)
{
	char	**result;
	int		i;

	i = 0;
	result = gc_malloc(sizeof(char *) * (lst_size(env) + 1));
	while (env)
	{
		result[i] = ft_strsjoin(3, env->name, "=", env->value);
		env = env->next;
		i++;
	}
	result[i] = NULL;
	return (result);
}

void	execve_fail(t_command *cmd)
{
    if (errno == ENOENT)
        print_error(cmd->argv[0], "command not found", 127);
    else if (errno == EACCES)
        print_error(cmd->argv[0], "permission denied", 126);
    else
        print_error(cmd->argv[0], strerror(errno), 1);
}

char	*check_path(char *cmd)
{
	if (access(cmd, F_OK) || access(cmd, X_OK))
	{
		print_error("path", strerror(errno), errno);
		exit(g_exit_code);
	}
	return (ft_strdup(cmd));
}

char	*this_is_the_path(char **path, char *cmd)
{
	char	*cmd_path;
	int		i;

	i = 0;
	if (ft_strchr(cmd, '/'))
		return (check_path(cmd));
	while (path && path[i])
	{
		cmd_path = ft_strsjoin(3, path[i], "/", cmd);
		if (!access(cmd_path, X_OK) && !access(cmd_path, F_OK))
			return (cmd_path);
		else
			gc_free(cmd_path);
		i++;
	}
	print_error("minishell", "command not found", 127);
	exit(g_exit_code);
	return (NULL);
}

void	fork_init(t_exec *exec)
{
	ft_lstadd_back(&(exec->pid), ft_lstnew(-1));
	ft_lstlast(exec->pid)->data = fork();
	if (ft_lstlast(exec->pid)->data == -1)
	{
		print_error("problem with the fork", strerror(errno), g_exit_code);
		exit(g_exit_code);
	}		
}
