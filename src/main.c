#include "executing.h"

t_command	*tester(t_command *cmd)
{
	(void)cmd;
	return (cmd);
}

int	main(int argc, char **argv, char **env)
{
	t_exec		exec;
	t_command	cmd;

	tester(&cmd);
	struct_init(&exec, &cmd, env);
	here_doc_verif(&exec, argc, argv);
	parent(&cmd, &exec);
	free_all(&exec, FREE_LST);
	return (0);
}
