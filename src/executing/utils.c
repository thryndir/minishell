#include "executing.h"

int	read_or_write(int read_or_write, t_redir *redir, t_exec exec)
{
	int	fd;
	int	flag;

	fd = -1;
	flag = O_TRUNC;
	if (!ft_strcmp(redir->file, "/tmp/temp"))
		flag = O_APPEND;
	if (read_or_write == READ)
		fd = open(redir->file, O_RDONLY);
	else
		fd = open(redir->file, O_WRONLY | O_CREAT | flag, 0644);
	if (fd == -1)
		ft_error("problem when opening the file: ", &exec, FREE_LST, 1);
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

void	close_pipe(t_exec *exec)
{
	int	i;

	i = 0;
	while (i < exec->cmd_nbr - 1)
	{
		close(exec->pipe_fd[i][0]);
		close(exec->pipe_fd[i][1]);
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
	if (which >= 2 && pipex->env != NULL)
		del_env(pipex->env);
	if (which >= 3 && pipex->p_path != NULL)
		double_array_free(pipex->p_path);
	if (which >= 4)
		close_pipe(pipex->pipe_fd, pipex->cmd_nbr);
	if (which >= 5 && pipex->pipe_fd != NULL)
		free(pipex->pipe_fd);
	if (which >= 6 && pipex->cmds != NULL)
		double_array_free(pipex->cmds);
	if (which >= 7 && pipex->path != NULL)
		free(pipex->path);
	if (which >= 8 && pipex->lst != NULL)
		free_lst(pipex->lst);
}
