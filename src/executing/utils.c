#include "executing.h"

int	read_or_write(int read_or_write, t_redir *redir)
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
		ft_error("problem when opening the file: ");
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

// void	free_all(t_exec *exec, int which)
// {
// 	if (which >= 2 && exec->env != NULL)
// 		del_env(exec->env);
// 	if (which >= 3 && exec->p_path != NULL)
// 		double_array_free(exec->p_path);
// 	if (which >= 4)
// 		close_pipe(exec->pipe_fd, exec->cmd_nbr);
// 	if (which >= 5 && exec->pipe_fd != NULL)
// 		free(exec->pipe_fd);
// 	if (which >= 6 && exec->cmds != NULL)
// 		double_array_free(exec->cmds);
// 	if (which >= 7 && exec->path != NULL)
// 		free(exec->path);
// 	if (which >= 8 && exec->lst != NULL)
// 		free_lst(exec->lst);
// }
