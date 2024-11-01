#include "executing.h"

void	init_pipe(int *pipe_fds[2])
{
	if (pipe(pipe_fds[0]) == -1)
		ft_error();
	if (pipe(pipe_fds[1]) == -1)
		ft_error();
}

int	runner(t_command *cmd, t_exec *exec)
{
	t_builtin	*htable;

	htable = htable_get(cmd->name, ft_strlen(cmd->name));
	if (htable)
	{
		htable->builtin_func(exec);
		return;
	}
	fork_init(exec);
	init_pipe(exec->pipe_fds);
	if (ft_lstlast(exec->pid)->data == 0)
	{
		redirect(cmd, exec);
		child(exec, cmd);
	}
	return (0);
}

int	last_fd_type(int type, t_redir *redir)
{
	t_redir *current;
	int		last_fd;

	current = redir;
	last_fd = type;
	while (current)
	{
		if (current->type == type)
			last_fd = current->fd;
		current = current->next;
	}
	return (last_fd);
}

void	prioritize_pipe(t_command *cmd, t_exec exec)
{
	if (exec.cmd_nbr == 1)
		return;
	if (cmd->index == 0)
		cmd->fd_out = exec.pipe_fd[cmd->index][1];
	if (cmd->index == exec.cmd_nbr - 1)
		cmd->fd_in = exec.pipe_fd[cmd->index - 1][0];
}

void	redirect(t_command *cmd, t_exec *exec)
{
	t_redir	*current;

	current = cmd->redirections;
	while (current)
	{
		if (current->type == REDIR_IN)
			current->fd = read_or_write(READ, current, *exec);
		else if (current->type == REDIR_OUT)
			current->fd = read_or_write(WRITE, current, *exec);
		current = current->next;
	}
	cmd->fd_in = last_fd_type(REDIR_IN, cmd->redirections);
	cmd->fd_out = last_fd_type(REDIR_OUT, cmd->fd_out);
	prioritize_pipe(cmd, *exec);
}

void	child(t_exec *exec, t_command *cmd)
{
	t_builtin	*htable;
	char 		**env;

	lst_to_array(exec->cmd, env);
	dup2(cmd->fd_in, 0);
	dup2(cmd->fd_out, 1);
	if (cmd->redirections)
		close_fd(cmd->redirections);
	close_pipe(exec);
	htable = htable_get(cmd->name, ft_strlen(cmd->name));
	if (htable)
		htable->builtin_func(exec);
	else if (cmd->path != NULL)
		execve(cmd->path, cmd->args, env);
	ft_dprintf(2, "minishell: command not found: %s\n", cmd->name);
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
