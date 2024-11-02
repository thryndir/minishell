
#ifndef EXECUTING_H
# define EXECUTING_H

# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>
# include <stdbool.h>
# include "libft.h"
# include "parsing.h"
# include <assert.h>

# define TOTAL_KEYWORDS 7
# define MIN_WORD_LENGTH 2
# define MAX_WORD_LENGTH 6
# define MIN_HASH_VALUE 2
# define MAX_HASH_VALUE 9

typedef enum e_read_or_write
{
	READ,
	WRITE
}	t_read_or_write;

typedef enum e_error
{
	WRITE_MSG = 1,
	FREE_ENV,
	FREE_P_PATH,
	CLOSE_PIPE,
	FREE_PIPE,
	FREE_CMD,
	FREE_PATH,
	FREE_LST,
}	t_error;

typedef struct s_env
{
	struct s_env	*next;
	char			*name;
	char			*value;
}	t_env;

typedef struct exec
{
	char		**p_path;
	int			cmd_nbr;
	t_command	*cmd;
	t_env		*env;
	t_list		*pid;
	int			status;
}	t_exec;

typedef struct s_builtin
{
	const char	*key;
	int			(*builtin_func)(t_exec *);
}	t_builtin;

char		**search_in_env(char **env);
void		pipe_parent(char **argv, int end, t_exec *exec);
void		ft_error(char *message, t_exec *exec, int which, int status);
char		*this_is_the_path(t_exec *exec, char **p_path, char **cmd);
void		free_all(t_exec *exec, int which);
void		init_exec(t_exec *exec, char *cmd);
void		return_code(t_exec *exec);
void		double_array_free(char **strs);
int			runner(t_command *cmd, t_exec *exec, int pipe_fds[2]);
void		fork_init(t_exec *exec);
void		no_pipe_parent(char **argv, int end, t_exec *exec);
void		no_pipe_child(t_exec *exec);
void		no_pipe_init(t_exec *exec, char **argv, int argc);
void		init_pipe_fds(t_exec *exec);
void		struct_init(t_exec *exec, char **argv, int argc, char **env);
void		last_child(int current, t_exec *exec, int (*pipe_fd)[2]);
void		first_child(int current, t_exec *exec, int (*pipe_fd)[2]);
void		child(t_exec *exec, t_command *cmd);
void		close_pipe(t_exec *exec);
void		here_doc(t_exec *exec, char *lim);
int			read_or_write(int read_or_write, t_redir *redir, t_exec exec);
void		here_doc_verif(t_exec *exec, int argc, char **argv);
void		hold_on(t_list *lst, int *status);
t_builtin	*htable_get(const char *str, size_t len);
int			echo_builtin(t_exec *exec);
int			cd_builtin(t_exec *exec);
int			env_builtin(t_exec *exec);
int			exit_builtin(t_exec *exec);
int			export_builtin(t_exec *exec);
int			pwd_builtin(t_exec *exec);
int			unset_builtin(t_exec *exec);
void		free_env(t_env *env);
int			env_init(char **envp, t_exec *exec);
int			pos_in_str(char *str, char to_search);
void		del_in_env(t_env **env, t_env *to_delete);
void		add_in_env(t_env *env, char *name, char *value);
void		ft_envadd_back(t_env **env, t_env *new);
t_env		*ft_envnew(char *var);
t_env		*ft_envlast(t_env *env);
void		print_lst(t_env *env);
char		*ft_strsjoin(int str_nbr, ...);
int			name_and_value(char *var, t_env *env);
void		del_env(t_env *env);
char		*get_value(t_env *env, char *name);

#endif
