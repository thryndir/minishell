#include "executing.h"

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
	fd = read_or_write(WRITE, redir);
	if (fd == -1)
		ft_error("here_doc failed to open tmpfile in /tmp: ", 1, exit_code);
	redir->file = "/tmp/temp";
	redir->type = REDIR_IN;
	while (1)
	{
		str = readline("heredoc :");
		temp = ft_strtrim(str, "\n");
		if (str == NULL || !ft_strcmp(temp, lim))
			break ;
		write(fd, str, ft_strlen(str));
		gc_free(str);
		gc_free(temp);
	}
	gc_free(str);
	gc_free(temp);
	verif_and_close(&fd);
}
