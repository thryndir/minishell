#include "executing.h"	

int	last_fd_type(int type, t_command *cmd, t_redir *redir, int pipe_fds[2])
{
	t_redir *current;
	int		last_fd;

	current = redir;
	last_fd = -1;
	while (current)
	{
		if ((int)(current->type) == type)
			last_fd = current->fd;
		current = current->next;
	}
	if (type == REDIR_IN && last_fd != -1)
	{
		cmd->fd_in = last_fd;
		verif_and_close(&pipe_fds[0]);
	}
	else if ((type == REDIR_OUT || type == REDIR_APPEND) && last_fd != -1)
	{
		cmd->fd_out = last_fd;
		verif_and_close(&pipe_fds[1]);
	}
	return (last_fd);
}

void	pipe_redir(t_command *cmd, t_exec exec, int pipe_fds[2])
{
	if (exec.cmd_nbr == 1)
		return;
	if (cmd->index == 0)
	{
		cmd->fd_out = pipe_fds[1];
		verif_and_close(&pipe_fds[0]);
	}
	else if (cmd->index == (exec.cmd_nbr - 1))
	{
		cmd->fd_in = pipe_fds[0];
		verif_and_close(&pipe_fds[1]);
	}
	else
	{
		cmd->fd_in = pipe_fds[0];
		cmd->fd_out = pipe_fds[1];
	}
}

void	redirect(t_command *cmd, t_exec *exec, int pipe_fds[2])
{
	t_redir	*current;

	current = cmd->redirections;
	while (current)
	{
		if (current->type == REDIR_IN)
			current->fd = read_or_write(READ, current);
		else if (current->type == REDIR_OUT || current->type == REDIR_APPEND)
			current->fd = read_or_write(WRITE, current);
		current = current->next;
	}
	pipe_redir(cmd, *exec, pipe_fds);
	last_fd_type(REDIR_IN, cmd, cmd->redirections, pipe_fds);
	last_fd_type(REDIR_OUT, cmd, cmd->redirections, pipe_fds);
	last_fd_type(REDIR_APPEND, cmd, cmd->redirections, pipe_fds);
}

int	runner(t_command *cmd, t_exec *exec, int *pipe_fds, int next_out)
{
	t_builtin	*htable;
	char		**path;

	htable = htable_get(cmd->argv[0], ft_strlen(cmd->argv[0]));
	if (htable && exec->cmd_nbr > 1)
	{
		redirect(cmd, exec, pipe_fds);
		htable->builtin_func(cmd, exec);
		return (0);
	}
	path = ft_split(get_value(exec->env, "PATH"), ':');
	cmd->path = this_is_the_path(path, cmd->argv[0]);
	fork_init(exec);
	if (ft_lstlast(exec->pid)->data == 0)
	{
		redirect(cmd, exec, pipe_fds);
		dprintf(2, "enfant cmd nbr : %d\n", cmd->index);
		child(exec, cmd, next_out);
	}
	return (0);
}

int	lst_size(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		env = env->next;
		i++;
	}
	return (i);
}

char **lst_to_array(t_env *env)
{
	char 	**result;
	char	*var;
	int		i;

	i = 0;
	result = malloc(sizeof(char *) * (lst_size(env) + 1));
	while (env)
	{
		var = ft_strsjoin(3, env->name, "=", env->value);
		result[i] = ft_strdup(var);
		free(var);
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

void print_open_fds(const char *where)
{
	int	fd;

	fd = 0;
	while (fd < 10)
	{
		if (fcntl(fd, F_GETFD) != -1) 
			dprintf(2, "%s - FD %d is open (PID: %d)\n", where, fd, getpid());
		fd++;
	}
}

void	child(t_exec *exec, t_command *cmd, int next_out)
{
	char 		**env;
	t_builtin	*htable;

	env = lst_to_array(exec->env);
	dprintf(2, "fd_in = %d, fd_out = %d, next_out = %d\n", cmd->fd_in, cmd->fd_out, next_out);
	if (cmd->fd_in != -1)
		dup2(cmd->fd_in, STDIN_FILENO);
	if (cmd->fd_out != -1)
		dup2(cmd->fd_out, STDOUT_FILENO);
	if (cmd->redirections)
		close_all(cmd);
	verif_and_close(&cmd->fd_in);
	verif_and_close(&cmd->fd_out);
	verif_and_close(&next_out);
	htable = htable_get(cmd->argv[0], ft_strlen(cmd->argv[0]));
	print_open_fds("child process");
	if (htable)
	{
		htable->builtin_func(cmd, exec);
		return;
	}
	else
		execve(cmd->path, cmd->argv, env);
	dprintf(2, "minishell: command not found: %s\n", cmd->argv[0]);
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
