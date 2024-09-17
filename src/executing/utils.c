/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 16:14:25 by lgalloux          #+#    #+#             */
/*   Updated: 2024/09/17 12:52:00 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	read_or_write(char *file, int read_or_write, t_pipex pipex)
{
	int	fd;
	int	flag;

	fd = -1;
	flag = O_TRUNC;
	if (!ft_strcmp(pipex.infile, "/tmp/temp"))
		flag = O_APPEND;
	if (read_or_write == READ)
		fd = open(file, O_RDONLY);
	else
		fd = open(file, O_WRONLY | O_CREAT | flag, 0644);
	if (fd == -1)
		ft_error("problem when opening the file: ", &pipex, FREE_LST, 1);
	return (fd);
}

void	double_array_free(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

void	close_pipe(int (*pipe_fd)[2], int cmd_nbr)
{
	int	i;

	i = 0;
	while (i < cmd_nbr - 1)
	{
		close(pipe_fd[i][0]);
		close(pipe_fd[i][1]);
		i++;
	}
}

void	free_lst(t_list *lst)
{
	t_list	*temp;

	while (lst)
	{
		temp = lst->next;
		free(lst);
		lst = temp;
	}
}

void	free_all(t_pipex *pipex, int which)
{
	if (which >= 2 && pipex->p_path != NULL)
		double_array_free(pipex->p_path);
	if (which >= 3)
		close_pipe(pipex->pipe_fd, pipex->cmd_nbr);
	if (which >= 4 && pipex->pipe_fd != NULL)
		free(pipex->pipe_fd);
	if (which >= 5 && pipex->cmd != NULL)
		double_array_free(pipex->cmd);
	if (which >= 6 && pipex->path != NULL)
		free(pipex->path);
	if (which >= 7 && pipex->lst != NULL)
		free_lst(pipex->lst);
}
