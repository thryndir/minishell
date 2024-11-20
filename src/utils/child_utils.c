/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 20:18:40 by lgalloux          #+#    #+#             */
/*   Updated: 2024/11/20 12:00:52 by lgalloux         ###   ########.fr       */
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

void	close_all(t_command *cmd)
{
	t_redir		*redir;

	redir = cmd->redirections;
	while (redir)
	{
		verif_and_close(&redir->fd);
		redir = redir->next;
	}
}

void	execve_fail(char *path, int status)
{
	if (!access(path, X_OK))
	{
		dprintf(2, "%s %s\n", strerror(errno), path);
		exit (status);
	}
	else if (!access(path, F_OK))
	{
		dprintf(2, "command not found : %s\n", path);
		exit(127);
	}
}

char	*this_is_the_path(char **path, char *cmd)
{
	char	*cmd_path;
	int		i;

	i = 0;
	if (cmd == NULL)
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	while (path[i])
	{
		cmd_path = ft_strsjoin(3, path[i], "/", cmd);
		if (cmd_path == NULL)
			return (NULL);
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		else
			gc_free(cmd_path);
		i++;
	}
	return (NULL);
}

void	fork_init(t_exec *exec)
{
	ft_lstadd_back(&(exec->pid), ft_lstnew(-1));
	ft_lstlast(exec->pid)->data = fork();
	if (ft_lstlast(exec->pid)->data == -1)
		ft_error("problem with the fork: ", 1, g_exit_code);
}
