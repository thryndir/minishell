#include "executing.h"

int	env_builtin(t_command *cmd, t_exec *exec)
{
	t_env	*current;
	(void)cmd;

	current = exec->env;
	while (current != NULL)
	{
		if (current->name && current->value)
			printf("%s=%s\n", current->name, current->value);
		else
			dprintf(2, "Invalid environment variable\n");
		current = current->next;
	}
	return (0);
}
