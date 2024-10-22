#include "minishell.h"

void	free_env(t_env *env)
{
	t_env	*temp;

	while (env)
	{
		temp = env->next;
		free(env->value);
		free(env->name);
		free(env);
		env = temp;
	}
}

void	struct_init(t_pipex *pipex, char **argv, int argc, char **envp)
{
	pipex->cmds = NULL;
	pipex->path = NULL;
	pipex->pipe = 0;
	pipex->status = 0;
	pipex->p_path = search_in_env(envp);
	if (pipex->p_path == NULL)
		ft_error("problem when searching in the env\n", pipex, -WRITE_MSG, 1);
	pipex->outfile = argv[argc - 1];
	if (!pipex->pipe)
		pipex->cmd_nbr = argc - 1;
	else if (pipex->here_doc)
	{
		pipex->cmd_nbr = argc - 4;
		pipex->infile = "/tmp/temp";
	}
	else
	{
		pipex->cmd_nbr = argc - 3;
		pipex->infile = argv[1];
	}
	pipex->envp = envp;
	env_init(envp, pipex);
	pipex->lst = NULL;
}

char	**search_in_env(char **envp)
{
	int		i;
	char	**path;
	char	*tmp;

	i = 0;
	path = NULL;
	while (ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	path = ft_split(envp[i], ':');
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
