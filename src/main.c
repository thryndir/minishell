#include "executing.h"

int	main(int argc, char **argv, char **env)
{
	t_pipex		pipex;

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
