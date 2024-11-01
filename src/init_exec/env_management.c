#include "executing.h"

void	ft_envadd_back(t_env **env, t_env *new)
{
	t_env	*temp;

	if (env == NULL)
		*env = new;
	else
	{
		temp = ft_envlast(*env);
		temp->next = new;
	}
}

void	del_env(t_env *env)
{
	t_env	*temp;

	while (env)
	{
		temp = env->next;
		free(env->name);
		free(env->value);
		free(env);
		env = temp;
	}
}

void	del_in_env(t_env **env, t_env *to_delete)
{
	t_env	*current;

	current = *env;
	while (current && current->next != to_delete && current != to_delete)
		current = current->next;
	if (*env == to_delete)
		*env = (*env)->next;
	else
		current->next = to_delete->next;
	free(to_delete->name);
	free(to_delete->value);
	free(to_delete);
}

void	add_in_env(t_env *env, char *name, char *value)
{
	t_env	*current;
	char	*var;

	current = env;
	while (current)
	{
		if (!ft_strcmp(current->name, name) && ft_strcmp(current->value, value))
		{
			current->value = ft_strdup(value);
			return ;
		}
		current = current->next;
	}
	var = ft_strsjoin(3, name, "=", value);
	ft_envadd_back(&env, ft_envnew(var));
	free(var);
}

char	*get_value(t_env *env, char *name)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (!ft_strcmp(current->name, name))
			return (current->value);
		current = current->next;
	}
	return (NULL);
}
