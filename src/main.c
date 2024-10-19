

#include "minishell.h"

// void	which_exec(t_cmd *cmd)
// {
// 	if (premier token est un systeme)
// 		execute_system(...);
// 	else
// 		execute_others(...);
// 	if (cmd->pipe)
// 		execute(cmd->pipe);
// }

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
