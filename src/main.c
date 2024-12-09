/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thryndir <thryndir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 20:44:38 by lgalloux          #+#    #+#             */
/*   Updated: 2024/12/09 13:42:17 by thryndir         ###   ########.fr       */
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

void	print_redirection(t_redir *redir)
{
	while (redir)
	{
		ft_printf("    Redirection:\n");
		ft_printf("      Type: ");
		if (redir->type == REDIR_IN)
		{
			ft_printf("REDIR_IN (<)\n");
		}
		if (redir->type == REDIR_OUT)
		{
			ft_printf("REDIR_OUT (>)\n");
		}
		if (redir->type == REDIR_APPEND)
		{
			ft_printf("REDIR_APPEND (>>)\n");
		}
		if (redir->type == REDIR_HEREDOC)
		{
			ft_printf("REDIR_HEREDOC (<<)\n");
		}
		ft_printf("      File: %s\n", redir->file);
		ft_printf("      FD: %d\n", redir->fd);
		redir = redir->next;
	}
}

void	print_command(t_command *cmd)
{
	t_command *current;

	current = cmd;
	while (current)
	{
		ft_printf("Command %d:\n", current->index);
		ft_printf("  Path: %s\n", current->path ? cmd->path : "NULL");
		ft_printf("  FD in: %d\n", current->fd_in);
		ft_printf("  FD out: %d\n", current->fd_out);
		ft_printf("  Arguments (%d):\n", current->argc);
		if (current->argv)
		{
			for (int i = 0; current->argv[i]; i++)
			{
				ft_printf("    arg[%d]: %s\n", i, current->argv[i]);
			}
		}
		if (current->redirections)
		{
			print_redirection(current->redirections);
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
		loop_env_swapper(splitted_input, exec.env);
		exec.cmd = parse_input(splitted_input);
		loop_quote_handler(exec.cmd);
		struct_init(&exec, exec.cmd);
		print_command(exec.cmd);
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
