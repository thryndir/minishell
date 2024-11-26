/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgerbaul <jgerbaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 20:44:38 by lgalloux          #+#    #+#             */
/*   Updated: 2024/11/26 23:13:05 by jgerbaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

int	g_exit_code = 0;

int	main(int argc, char **argv, char **env)
{
	t_exec	exec;
	char	*input;
	char	**splitted_input;

	(void)argc;
	(void)argv;
	set_signal();
	while (1)
	{
		input = readline(">> ");
		if (!input)
			break ;
		if (!syntax_checker(input))
			continue ; 
		add_history(input);
		splitted_input = ft_mini_split(input);
		exec.cmd = parse_input(splitted_input);
		struct_init(&exec, exec.cmd, env);
		parent(exec.cmd, &exec, 0);
		free_cmd_exec(&exec, NULL);
		gc_tab_free(splitted_input);
		gc_free(input);
	}
	free_env(exec.env);
}

/*
int	main(int argc, char **argv, char **env)
{
	t_exec		exec;

	(void)argc;
	(void)argv;
	exec.cmd = NULL;
	tester(&exec.cmd);
	struct_init(&exec, exec.cmd, env);
	parent(exec.cmd, &exec, 0);
	free_cmd_exec(&exec, NULL);
	free_env(exec.env);
	return (0);
}
*/
