#include "executing.h"

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

char **tabdup(char **args, int argc)
{
	char **result;
	int	i;
	
	i = 0;
	if (!args)
		return (NULL);
	result = malloc(sizeof(char *) * argc);
	if (!result)
		return (NULL);
	while (args && i < argc)
	{
		result[i] = ft_strdup(args[i]);
		i++;
	}
	result[i] = NULL;
	return (result);
}

t_command	*cmdnew(char *name, char **args, int argc, t_redir *redirection)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->name = ft_strdup(name);
	cmd->args = tabdup(args, argc);
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

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->next = NULL;
	redir->type = type;
	redir->fd = -1;
	redir->file = ft_strdup(file);
	return (redir);
}

//ls | sort

void	tester(t_command **cmd)
{
	cmdadd_back(cmd, cmdnew("ls", NULL, 1, NULL));
	cmdadd_back(cmd, cmdnew("sort", NULL, 1, NULL));
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
	return (0);
}
