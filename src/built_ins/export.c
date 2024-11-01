#include "executing.h"

void	sort_env(t_env *env)
{
	t_env	*i;
	t_env	*j;
	char	*tmp;

	i = env;
	while (i->next)
	{
		j = i->next;
		while (j->next)
		{
			if (ft_strcmp(i->name, j->name) > 0)
			{
				tmp = i->name;
				i->name = j->name;
				j->name = tmp;
				tmp = i->value;
				i->value = j->value;
				j->value = tmp;
			}
			j = j->next;
		}
		i = i->next;
	}
}

t_env	*env_copy(t_env *env)
{
	t_env	*current;
	t_env	*new;
	char	*var;

	current = env;
	var = ft_strsjoin(3, current->name, "=", current->value);
	new = ft_envnew(var);
	free(var);
	current = current->next;
	while (current)
	{
		var = ft_strsjoin(3, current->name, "=", current->value);
		ft_envadd_back(&new, ft_envnew(var));
		free(var);
		current = current->next;
	}
	return (new);
}

int	export_builtin(t_pipex *pipex)
{
	t_env	*copy;
	t_env	*temp;

	temp = NULL;
	copy = env_copy(pipex->env);
	if (pipex->cmds[1] == NULL)
	{
		sort_env(copy);
		print_lst(copy);
	}
	else
	{
		temp = ft_envnew(pipex->cmds[1]);
		add_in_env(pipex->env, temp->name, temp->value);
	}
	del_env(temp);
	del_env(copy);
	return (0);
}
