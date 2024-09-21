/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thryndir <thryndir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 22:34:37 by lgalloux          #+#    #+#             */
/*   Updated: 2024/09/21 18:15:09 by thryndir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fork_init(t_pipex *pipex)
{
	ft_lstadd_back(&(pipex->lst), ft_lstnew(-1));
	ft_lstlast(pipex->lst)->data = fork();
	if (ft_lstlast(pipex->lst)->data == -1)
		ft_error("problem with the fork: ", pipex, FREE_LST, 1);
}

char	*this_is_the_path(t_pipex *pipex, char **p_path, char **cmd)
{
	char	*path;
	char	*tmp;
	int		i;

	i = 0;
	if (cmd[0] == NULL)
		return (NULL);
	if (access(cmd[0], X_OK) == 0)
		return (ft_strdup(cmd[0]));
	while (p_path[i])
	{
		tmp = ft_strjoin("/", cmd[0]);
		if (tmp == NULL)
			ft_error("malloc failed\n", pipex, -FREE_CMD, 1);
		path = ft_strjoin(p_path[i], tmp);
		if (path == NULL)
			return (NULL);
		free(tmp);
		if (access(path, X_OK) == 0)
			return (path);
		else
			free(path);
		i++;
	}
	return (NULL);
}

void	init_exec(t_pipex *pipex, char *cmd)
{
	if (pipex->cmds != NULL)
		double_array_free(pipex->cmds);
	pipex->cmds = ft_split(cmd, ' ');
	if (pipex->cmds == NULL)
		ft_error("problem with the first split\n", pipex, -FREE_PIPE, 1);
	if (pipex->path != NULL)
		free(pipex->path);
	pipex->path = this_is_the_path(pipex, pipex->p_path, pipex->cmds);
}
