/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 20:32:45 by lgalloux          #+#    #+#             */
/*   Updated: 2024/10/01 12:30:09 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

t_env	*ft_envlast(t_env *env)
{
	if (env == NULL)
		return (NULL);
	while (env->next != NULL)
	{
		env = env->next;
	}
	return (env);
}

int		pos_in_str(char *str, char to_search)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != to_search)
		i++;
	return (i);
}

void	ft_envadd_back(t_env **env, t_env *new)
{
	t_env	*temp;

	if (env == NULL)
		*env = new;
	else
	{
		temp = ft_envlast(*env);
		temp->next = new;
		new->previous = temp;
	}
}

void	name_and_value(char *var, t_env *env)
{
	int	i;
	int	j;
	int	pos;

	i = 0;
	j = 0;
	pos = pos_in_str(var, '=');
	env->name = ft_calloc(pos, sizeof(char));
	env->value = ft_calloc(ft_strlen(var) - (pos + 1), sizeof(char));
	while (var[i] && var[i] != '=')
	{
		env->name[i] = var[i];
		i++;
	}
	i++;
	while (var[i])
	{
		env->value[j] = var[i];
		i++;
		j++;
	}
}

t_env	*ft_envnew(char *var)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	name_and_value(var, env);
	env->next = NULL;
	env->previous = NULL;
	return (env);
}

void	env_init(char **envp, t_pipex *pipex)
{
	int	i;
	pipex->env = ft_envnew(envp[0]);

	i = 1;
	while (envp[i])
	{
		ft_envadd_back(&(pipex->env), ft_envnew(envp[i]));
		i++;
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
