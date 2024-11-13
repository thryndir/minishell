#include "executing.h"

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

int	get_cmd_nbr(t_command *cmd)
{
	t_command 	*current;
	t_redir		*redir;
	int			cmd_nbr;

	cmd_nbr = 0;
	current = cmd;
	while (current)
	{
		redir = current->redirections;
		if (redir && redir->type == REDIR_HEREDOC)
			here_doc(redir);
		current->index = cmd_nbr;
		current = current->next;
		cmd_nbr++;
	}
	return (cmd_nbr);
}

int	struct_init(t_exec *exec, t_command *cmd, char **envp)
{
	exec->status = 0;
	if (env_init(envp, exec))
		return (1);
	exec->cmd_nbr = get_cmd_nbr(cmd);
	exec->pid = NULL;
	return (0);
}

void	here_doc(t_redir *redir)
{
	char	*str;
	char	*temp;
	char	*lim;
	int		fd;

	lim = redir->file;
	fd = open("/tmp/temp", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		ft_error("here_doc failed to open tmpfile in /tmp: ");
	redir->file = "/tmp/temp";
	redir->type = REDIR_IN;
	while (1)
	{
		write(1, "exec heredoc> ", 15);
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
	verif_and_close(&fd);
}
