/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgerbaul <jgerbaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 20:44:38 by lgalloux          #+#    #+#             */
/*   Updated: 2024/12/05 23:39:32 by jgerbaul         ###   ########.fr       */
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
/*
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
*/

void	print_redirection(t_redir *redir)
{
	while (redir)
	{
		printf("    Redirection:\n");
		printf("      Type: ");
		if (redir->type == REDIR_IN)
		{
			printf("REDIR_IN (<)\n");
		}
		if (redir->type == REDIR_OUT)
		{
			printf("REDIR_OUT (>)\n");
		}
		if (redir->type == REDIR_APPEND)
		{
			printf("REDIR_APPEND (>>)\n");
		}
		if (redir->type == REDIR_HEREDOC)
		{
			printf("REDIR_HEREDOC (<<)\n");
		}
		printf("      File: %s\n", redir->file);
		printf("      FD: %d\n", redir->fd);
		redir = redir->next;
	}
}

void	print_command(t_command *cmd)
{
	printf("Command %d:\n", cmd->index);
	printf("  Path: %s\n", cmd->path ? cmd->path : "NULL");
	printf("  FD in: %d\n", cmd->fd_in);
	printf("  FD out: %d\n", cmd->fd_out);
	printf("  Arguments (%d):\n", cmd->argc);
	if (cmd->argv)
	{
		for (int i = 0; cmd->argv[i]; i++)
		{
			printf("    arg[%d]: %s\n", i, cmd->argv[i]);
		}
	}
	if (cmd->redirections)
	{
		print_redirection(cmd->redirections);
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
		loop_env_swapper(splitted_input, exec.env);
		remove_quotes_from_argv(splitted_input);
		exec.cmd = parse_input(splitted_input);
		struct_init(&exec, exec.cmd);


		t_command *current = exec.cmd;
		while (current)
		{
			print_command(current);
			current = current->next;
		}
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
