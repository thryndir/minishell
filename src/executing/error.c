#include "executing.h"

void	ft_error(char *message)
{
	ft_dprintf(2, "%s\n", message);
	exit(1);
}

// void	here_doc_verif(t_pipex *pipex, int argc, char **argv)
// {
// 	if (!ft_strcmp(argv[1], "here_doc"))
// 	{
// 		if (argc < 6)
// 			ft_error("wrong number of arguments\n", pipex, -WRITE_MSG, 1);
// 		pipex->here_doc = 1;
// 		here_doc(pipex, argv[2]);
// 	}
// }

void	return_code(t_exec *exec)
{
	if (WIFEXITED(exec->status))
	{
		if (WEXITSTATUS(exec->status) == 127)
			ft_error("command not found");
		ft_error("commande not found");
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
