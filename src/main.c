/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 20:44:38 by lgalloux          #+#    #+#             */
/*   Updated: 2025/01/03 16:37:00 by lgalloux         ###   ########.fr       */
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

void	main_loop(t_exec *exec)
{
	char	*input;
	char	**splitted_input;

	splitted_input = NULL;
	while (1)
	{
		input = readline(">> ");
		if (!input)
		{
			gc_free_all();
			exit(0);
		}
		add_history(input);
		if (syntax_errors(input))
			continue ;
		main_functions(exec, splitted_input, input);
		main_free_function(exec, splitted_input, input);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_exec	exec;

	(void)argv;
	if (argc > 1)
	{
		print_error("wrong number of arguments", NULL, 1);
		return (1);
	}
	set_signal();
	env_init(env, &exec);
	main_loop(&exec);
	free_env(exec.env);
	rl_clear_history();
}
