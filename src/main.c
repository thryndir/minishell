/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 20:44:38 by lgalloux          #+#    #+#             */
/*   Updated: 2024/12/04 17:37:33 by lgalloux         ###   ########.fr       */
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

void	print_cmd(t_command *cmd)
{
	t_command	*current;
	t_redir		*redir;
	int			i;

	current = cmd;
	i = 0;
	while (current)
	{
		ft_printf("Le node nbr %d a pour commande %s\n", current->index, current->argv[0]);
		while (current->argv[i])
		{
			ft_printf("l'argument nbr %d de la commande %s est %s\n", i, current->argv[0], current->argv[i]);
			i++;
		}
		redir = current->redirections;
		while (redir)
		{
			ft_printf("Les redirections qui lui sont associees ont pour file %s et comme type %d\n", redir->file, redir->type);
			redir = redir->next;
		}
		current = current->next;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_exec	exec;
	char	*input;
	char	**splitted_input;

	(void)argc;
	(void)argv;
	set_signal();
	env_init(env, &exec);
	while (1)
	{
		input = readline(">> ");
		if (!input)
			return (0);
		add_history(input);
		if (syntax_errors(input))
			continue ;
		splitted_input = ft_mini_split(input);
		remove_quotes_from_argv(splitted_input);
		exec.cmd = parse_input(splitted_input);
		struct_init(&exec, exec.cmd);
		loop_env_swapper(exec.cmd, exec.env);
		print_cmd(exec.cmd);
		parent(exec.cmd, &exec, 0);
		main_free_function(&exec, splitted_input, input);
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
