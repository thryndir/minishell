

#include "minishell.h"

// void	sort_env(t_env **env)
// {
// 	t_env	**current;
// 	t_env	*last;
// 	t_env	*temp;
	
// 	last = NULL;
// 	while (*env != last)
// 	{
// 		current = env;
// 		while ((*current)->next != last)
// 		{
// 			if (ft_strcmp((*current)->name, (*current)->next->name) > 0)
// 			{
// 				temp = (*current)->next;
// 				if (temp->next)
// 				(*current)->next = temp->next;
// 				temp->next = *current;
// 				(*current) = temp;
// 			}
// 			current = &(*current)->next;
// 		}
// 		last = *current;
// 	}
// }

void	sort_env(t_env *env)
{
	t_env	*i;
	t_env	*j;
	char *tmp;

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

	current = env;
	new = ft_envnew(ft_strsjoin(3, current->name, "=", current->value));
	current = current->next;
	while (current)
	{
		ft_envadd_back(&new, ft_envnew(ft_strsjoin(3, current->name, "=",
		current->value)));
		current = current->next;
	}
	return (new);
}

int	export_builtin(t_pipex *pipex)
{
	t_env	*copy;
	t_env	*temp;

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
	del_env(copy);
	exit (0);
}