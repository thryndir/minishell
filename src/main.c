/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: thryndir <thryndir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 20:44:38 by lgalloux          #+#    #+#             */
/*   Updated: 2024/12/07 17:09:16 by thryndir         ###   ########.fr       */
=======
/*   By: jgerbaul <jgerbaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 20:44:38 by lgalloux          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/12/07 00:22:54 by jgerbaul         ###   ########.fr       */
>>>>>>> 8db8136 (fixed env with without quote)
=======
/*   Updated: 2024/12/07 00:47:45 by jgerbaul         ###   ########.fr       */
>>>>>>> e64259f ('re're)
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
		ft_printf("Command %d:\n", cmd->index);
		ft_printf("  Path: %s\n", cmd->path ? cmd->path : "NULL");
		ft_printf("  FD in: %d\n", cmd->fd_in);
		ft_printf("  FD out: %d\n", cmd->fd_out);
		ft_printf("  Arguments (%d):\n", cmd->argc);
		if (cmd->argv)
		{
			for (int i = 0; cmd->argv[i]; i++)
			{
				ft_printf("    arg[%d]: %s\n", i, cmd->argv[i]);
			}
		}
		if (cmd->redirections)
		{
			print_redirection(cmd->redirections);
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
		// dprintf(1, "la var globale vaut : %d au debut du main\n", g_exit_code);
		input = readline(">> ");
		if (!input)
			return (0);
		add_history(input);
		if (syntax_errors(input))
			continue ;
		splitted_input = ft_mini_split(input);
		for (int i = 0; splitted_input[i]; i++)
		{
			printf("%s\n", splitted_input[i]);
		}
		loop_env_swapper(splitted_input, exec.env);
//		remove_quotes_from_argv(splitted_input);
		for (int i = 0; splitted_input[i]; i++)
		{
			printf("%s\n", splitted_input[i]);
		}
		exec.cmd = parse_input(splitted_input);
		// print_command(exec.cmd);
		struct_init(&exec, exec.cmd);
<<<<<<< HEAD
		// print_command(exec.cmd);
=======
		print_command(exec.cmd);
>>>>>>> 8db8136 (fixed env with without quote)
		parent(exec.cmd, &exec, 0);
		main_free_function(&exec, splitted_input, input);
		// dprintf(1, "la var globale vaut : %d a la fin du main\n", g_exit_code);
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
