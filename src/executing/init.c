/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 20:32:45 by lgalloux          #+#    #+#             */
/*   Updated: 2024/09/17 12:51:57 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	struct_init(t_pipex *pipex, char **argv, int argc, char **env)
{
	pipex->cmd = NULL;
	pipex->path = NULL;
	pipex->p_path = search_in_env(env);
	if (pipex->p_path == NULL)
		ft_error("problem when searching in the env\n", pipex, -WRITE_MSG, 1);
	pipex->outfile = argv[argc - 1];
	if (pipex->here_doc)
	{
		pipex->cmd_nbr = argc - 4;
		pipex->infile = "/tmp/temp";
	}
	else
	{
		pipex->cmd_nbr = argc - 3;
		pipex->infile = argv[1];
	}
	pipex->env = env;
	pipex->lst = NULL;
}

char	**search_in_env(char **env)
{
	int		i;
	char	**path;
	char	*tmp;

	i = 0;
	path = NULL;
	while (ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	path = ft_split(env[i], ':');
	if (path == NULL)
		return (NULL);
	tmp = ft_strtrim(path[0], "PATH=");
	if (tmp == NULL)
		return (NULL);
	free(path[0]);
	path[0] = tmp;
	return (path);
}

void	here_doc(t_pipex *pipex, char *lim)
{
	char	*str;
	char	*temp;
	int		fd;

	fd = open("/tmp/temp", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		ft_error("here_doc failed to open tmpfile in /tmp: ",
			pipex, FREE_P_PATH, 1);
	while (1)
	{
		write(1, "pipex heredoc> ", 15);
		str = get_next_line(0);
		temp = ft_strtrim(str, "\n");
		if (str == NULL || !ft_strcmp(temp, lim))
			break ;
		write(fd, str, ft_strlen(str));
		free(str);
		free(temp);
	}
	free(str);
	free(temp);
	close(fd);
}

void	init_pipe_fds(t_pipex *pipex)
{
	int	i;

	i = 0;
	pipex->pipe_fd = malloc((pipex->cmd_nbr - 1) * sizeof(int [2]));
	if (pipex->pipe_fd == NULL)
		ft_error("malloc fail\n", pipex, -FREE_P_PATH, 1);
	while (i < pipex->cmd_nbr - 1)
	{
		if (pipe(pipex->pipe_fd[i]) == -1)
			ft_error("pipe fail\n", pipex, -FREE_PIPE, 1);
		i++;
	}
}
