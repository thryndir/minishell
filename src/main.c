#include "executing.h"

int	exit_code = 0;

t_command	*cmdlast(t_command *cmd)
{
	if (cmd == NULL)
		return (NULL);
	while (cmd->next != NULL)
	{
		cmd = cmd->next;
	}
	return (cmd);
}

void	cmdadd_back(t_command **cmd, t_command *new)
{
	t_command	*tmp;

	if (*cmd == NULL)
		*cmd = new;
	else
	{
		tmp = cmdlast(*(cmd));
		tmp->next = new;
	}
}

t_command	*cmdnew(char *args, int argc, t_redir *redirection)
{
	t_command	*cmd;

	cmd = gc_malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->argv = ft_split(args, ' ');
	cmd->argc = argc;
	cmd->fd_in = -1;
	cmd->fd_out = -1;
	cmd->index = -1;
	cmd->path = NULL;
	cmd->redirections = redirection;
	cmd->next = NULL;
	return (cmd);
}

t_redir	*redirlast(t_redir *redir)
{
	if (!redir)
		return (NULL);
	while (redir->next)
		redir = redir->next;
	return (redir);
}

void	redir_add_back(t_redir **redir, t_redir *new)
{
	t_redir *temp;

	if (!redir)
	{
		*redir = new;
		return;
	}
	temp = redirlast(*redir);
	temp->next = new;
}

t_redir	*redirnew(t_redir_type type, char *file)
{
	t_redir	*redir;

	redir = gc_malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->next = NULL;
	redir->type = type;
	redir->fd = -1;
	redir->file = ft_strdup(file);
	return (redir);
}

// cat < test.c | cat << lim | cat >> papaye | cat > out |
void	tester(t_command **cmd)
{
	// t_command *last_cmd;

	cmdadd_back(cmd, cmdnew("ls", 1, redirnew(REDIR_IN, "test.c")));
	cmdadd_back(cmd, cmdnew("ls", 1, redirnew(REDIR_IN, "lim")));
	cmdadd_back(cmd, cmdnew("ls", 1, redirnew(REDIR_APPEND, "papaye")));
	cmdadd_back(cmd, cmdnew("ls", 1, redirnew(REDIR_OUT, "out")));
}

int	main(int argc, char **argv, char **env)
{
	t_exec		exec;

	(void)argc;
	(void)argv;
	exec.cmd = NULL;
	tester(&exec.cmd);
	struct_init(&exec, exec.cmd, env);
	parent(exec.cmd, &exec, 0);
	gc_free_all();
	free_env(exec.env);
	return (0);
}
