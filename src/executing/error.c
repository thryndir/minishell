#include "executing.h"

void	ft_error(char *message, t_pipex *pipex, int which, int status)
{
	if (which > 0 && errno != 0)
		ft_dprintf(2, "%s%s\n", message, strerror(errno));
	else if (which < 0)
		ft_dprintf(2, "%s", message);
	if (which < 0)
		free_all(pipex, which *= -1);
	else
		free_all(pipex, which);
	exit(status);
}

void	here_doc_verif(t_pipex *pipex, int argc, char **argv)
{
	if (!ft_strcmp(argv[1], "here_doc"))
	{
		if (argc < 6)
			ft_error("wrong number of arguments\n", pipex, -WRITE_MSG, 1);
		pipex->here_doc = 1;
		here_doc(pipex, argv[2]);
	}
}

void	return_code(t_pipex *pipex)
{
	if (WIFEXITED(pipex->status))
	{
		if (WEXITSTATUS(pipex->status) == 127)
			ft_error("", pipex, -FREE_LST, WEXITSTATUS(pipex->status));
		ft_error("", pipex,
			-FREE_LST, WEXITSTATUS(pipex->status));
	}
}

void	hold_on(t_list *lst, int *status)
{
	waitpid(lst->data, status, 0);
	lst = lst->next;
	while (lst)
	{
		waitpid(lst->data, NULL, 0);
		lst = lst->next;
	}
}
