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

void	redirect(t_command *cmd, t_exec *exec, int pipe_fds[2], int next_out)
{
	t_redir	*current;

	current = cmd->redirections;
	while (current)
	{
		if (current->type == REDIR_IN)
			current->fd = read_or_write(READ, current);
		else if (current->type == REDIR_OUT || current->type == REDIR_APPEND)
			current->fd = read_or_write(WRITE, current);
		if (current->fd == -1)
		{
			verif_and_close(&pipe_fds[0]);
			verif_and_close(&pipe_fds[1]);
			verif_and_close(&next_out);
			ft_error("minishell", 1, exit_code);
		}
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
	if (htable && exec->cmd_nbr == 1)
	{
		redirect(cmd, exec, pipe_fds, next_out);
		htable->builtin_func(cmd, exec);
		return (0);
	}
	path = ft_split(get_value(exec->env, "PATH"), ':');
	cmd->path = this_is_the_path(path, cmd->argv[0]);
	fork_init(exec);
	if (ft_lstlast(exec->pid)->data == 0)
	{
		redirect(cmd, exec, pipe_fds, next_out);
		// dprintf(2, "enfant cmd nbr : %d\n", cmd->index);
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
	int		i;

	i = 0;
	result = malloc(sizeof(char *) * (lst_size(env) + 1));
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

bool	contain_an_except(void **addrs, void *addr)
{
	int		i;
	bool	result;

	i = 0;
	result = false;
	while (addrs[i])
	{
		if (addrs[i] == addr)
			result = true;
		i++;
	}
	return (result);
}

void	gc_free_all_except(int addr_nbr, ...)
{
	va_list		arg;
	t_alloc_ptr	*lst;
	t_alloc_ptr	*tmp;
	void	**addr_array;
	int		i;

	i = 0;
	lst = addr_save(NULL, 1);
	va_start(arg, addr_nbr);
	addr_array = malloc(sizeof(void *) * (addr_nbr + 1));
	void **addr_array = (void **)(((void *)(&addr_nbr))+(24));
	addr_array[addr_nbr] = NULL;
	while (i < addr_nbr)
	{
		addr_array[i] = va_arg(arg, void *);
		i++;
	}
	while (lst)
	{
		tmp = lst->next;
		if (!contain_an_except(addr_array, lst->addr))
			gc_free(lst->addr);
		lst = tmp;
	}
	free(addr_array);
}

void	child(t_exec *exec, t_command *cmd, int next_out)
{
	char 		**env;
	t_builtin	*htable;

	env = lst_to_array(exec->env);
	// dprintf(2, "fd_in = %d, fd_out = %d, next_out = %d\n", cmd->fd_in, cmd->fd_out, next_out);
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
	// print_open_fds("child process");
	gc_free_all();
	if (htable)
	{
		exit_code = htable->builtin_func(cmd, exec);
		return;
	}
	else
		exit_code = execve(cmd->path, cmd->argv, env);
	execve_fail(cmd->path, exit_code);
}
