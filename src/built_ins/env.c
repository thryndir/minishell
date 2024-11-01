#include "executing.h"

int	env_builtin(t_pipex *pipex)
{
	t_env	*current;

	current = pipex->env;
	while (current != NULL)
	{
		if (current->name && current->value)
		{
			ft_dprintf(2, "%s=", current->name);
			ft_dprintf(2, "%s\n", current->value);
		}
		else
		{
			ft_dprintf(2, "Invalid environment variable\n");
		}
		current = current->next;
	}
	return (0);
}
