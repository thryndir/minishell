#include "executing.h"

void	ft_error(char *message)
{
	ft_dprintf(2, "%s\n", message);
	exit(1);
}

void	return_code(t_exec *exec)
{
	if (WIFEXITED(exec->status))
	{
		if (WEXITSTATUS(exec->status) == 127)
			ft_error("command not found");
		ft_error("command not found");
	}
}

void	hold_on(t_list *lst, int *status)
{
	(void)status;
	waitpid(lst->data, status, 0);
	lst = lst->next;
	while (lst)
	{
		waitpid(lst->data, NULL, 0);
		lst = lst->next;
	}
}
