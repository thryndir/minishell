/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:03:23 by lgalloux          #+#    #+#             */
/*   Updated: 2024/10/07 14:43:03 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_pipex		pipex;

	pipex.here_doc = 0;
	here_doc_verif(&pipex, argc, argv);
	struct_init(&pipex, argv, argc, env);
	init_pipe_fds(&pipex);
	if (!pipex.pipe)
		no_pipe_init(&pipex, argv, argc);
	else
		pipe_parent(argv, argc - 2, &pipex);
	free_all(&pipex, FREE_LST);
	return (0);
}
