#include "executing.h"

// void	ft_error(char *message, t_exec *exec, int which, int status)
// {
// 	if (which > 0 && errno != 0)
// 		ft_dprintf(2, "%s%s\n", message, strerror(errno));
// 	else if (which < 0)
// 		ft_dprintf(2, "%s", message);
// 	if (which < 0)
// 		free_all(exec, which *= -1);
// 	else
// 		free_all(exec, which);
// 	exit(status);
// }

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
			ft_error("", exec, -FREE_LST, WEXITSTATUS(exec->status));
		ft_error("", exec,
			-FREE_LST, WEXITSTATUS(exec->status));
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
