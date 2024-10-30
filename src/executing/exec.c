#include "minishell.h"

void	runner(t_command *cmd, t_exec *exec)
{
	t_builtin	*htable;

	htable = htable_get(cmd->name, ft_strlen(cmd->name));
	if (htable)
	{
		htable->builtin_func(exec);
		return;
	}
	if (exec->cmd_count == 0)

	fork_init(exec);
	if (ft_lstlast(exec->pid)->data == 0)
		middle_child(exec, exec->pipe_fd);
}

void	middle_child(t_exec *exec, int (*pipe_fd)[2])
{
	t_node		*node = exec->node;
	t_builtin	*htable;

	dup2(pipe_fd[exec->cmd_count - 1][0], 0);
	dup2(pipe_fd[exec->cmd_count][1], 1);
	close_pipe(pipe_fd, exec->cmd_nbr);
	htable = htable_get(node->u_u.cmd.name, ft_strlen(node->u_u.cmd.name));
	if (htable)
		htable->builtin_func(exec);
	else if (exec->node->u_u.cmd.path != NULL)
		execve(node->u_u.cmd.path, node->u_u.cmd.args, exec->envp);
	ft_dprintf(2, "minishell: command not found: %s\n", node->u_u.cmd.name);
	free_all(exec, FREE_LST);
	exit(127);
}

// void	pipe_parent(char **argv, int end, t_pipex *pipex)
// {
// 	int	start;

// 	if (pipex->here_doc)
// 		start = 3;
// 	else
// 		start = 2;
// 	init_exec(pipex, argv[end]);
// 	runner(end - start, pipex, LAST_CHILD);
// 	end--;
// 	while (end > start)
// 	{
// 		init_exec(pipex, argv[end]);
// 		runner(end - start, pipex, MIDDLE_CHILD);
// 		end--;
// 	}
// 	init_exec(pipex, argv[end]);
// 	runner(end - start, pipex, FIRST_CHILD);
// 	close_pipe(pipex->pipe_fd, pipex->cmd_nbr);
// 	hold_on(pipex->pid, &(pipex->status));
// 	if (WEXITSTATUS(pipex->status))
// 		return_code(pipex);
// }

// void	no_pipe_child(t_pipex *pipex)
// {
// 	t_builtin	*builtin;

// 	builtin = htable_get(pipex->cmds[0], ft_strlen(pipex->cmds[0]));
// 	if (builtin)
// 		builtin->builtin_func(pipex);
// 	else if (pipex->path != NULL)
// 		execve(pipex->path, pipex->cmds, pipex->envp);
// 	ft_dprintf(2, "pipex: command not found: %s\n", pipex->cmds[0]);
// 	free_all(pipex, FREE_LST);
// 	exit(127);
// }

// void	first_child(int current, t_exec *exec, int (*pipe_fd)[2])
// {
// 	int			fd;
// 	t_builtin	*builtin;

// 	builtin = htable_get(exec->cmds[0], ft_strlen(exec->cmds[0]));
// 	fd = read_or_write(exec->infile, READ, *exec);
// 	dup2(fd, 0);
// 	close(fd);
// 	dup2(pipe_fd[current][1], 1);
// 	close_pipe(pipe_fd, exec->cmd_nbr);
// 	if (builtin)
// 		builtin->builtin_func(exec);
// 	else if (exec->path != NULL)
// 		execve(exec->path, exec->cmds, exec->envp);
// 	ft_dprintf(2, "minishell: command not found: %s\n", exec->cmds[0]);
// 	free_all(exec, FREE_LST);
// 	exit(127);
// }

// void	last_child(int current, t_exec *exec, int (*pipe_fd)[2])
// {
// 	int			fd;
// 	t_builtin	*builtin;

// 	builtin = htable_get(exec->cmds[0], ft_strlen(exec->cmds[0]));
// 	fd = read_or_write(exec->outfile, WRITE, *exec);
// 	dup2(fd, 1);
// 	close(fd);
// 	dup2(pipe_fd[current - 1][0], 0);
// 	close_pipe(pipe_fd, exec->cmd_nbr);
// 	if (builtin)
// 		builtin->builtin_func(exec);
// 	else if (exec->path != NULL)
// 		execve(exec->path, exec->cmds, exec->envp);
// 	ft_dprintf(2, "minishell: command not found: %s\n", exec->cmds[0]);
// 	free_all(exec, FREE_LST);
// 	exit(127);
// }
