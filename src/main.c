/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgerbaul <jgerbaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 20:44:38 by lgalloux          #+#    #+#             */
/*   Updated: 2024/12/10 11:00:24 by jgerbaul         ###   ########.fr       */
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
		print_command(exec.cmd);
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
