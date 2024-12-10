/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgerbaul <jgerbaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 20:44:38 by lgalloux          #+#    #+#             */
/*   Updated: 2024/12/10 12:23:41 by jgerbaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

int	g_exit_code = 0;

void	main_free_function(t_exec *exec, char **tab, char *input)
{
	free_cmd_exec(exec, NULL);
	gc_tab_free(tab);
	gc_free(input);
}

void	main_functions(t_exec *exec, char **tab, char *str)
{
	tab = ft_mini_split(str);
	loop_env_swapper(tab, exec->env);
	exec->cmd = parse_input(tab);
	loop_quote_handler(exec->cmd);
	struct_init(exec, exec->cmd);
	parent(exec->cmd, exec, 0);
}

int	main(int argc, char **argv, char **env)
{
	t_exec	exec;
	char	*input;
	char	**splitted_input;

	splitted_input = NULL;
	(void)argc;
	(void)argv;
	set_signal();
	env_init(env, &exec);
	while (1)
	{
		input = readline(">> ");
		if (!input)
		{
			gc_free_all();
			return (0);
		}
		add_history(input);
		if (syntax_errors(input))
			continue ;
		main_functions(&exec, splitted_input, input);
		main_free_function(&exec, splitted_input, input);
	}
	free_env(exec.env);
}
