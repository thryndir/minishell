/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:30:43 by lgalloux          #+#    #+#             */
/*   Updated: 2024/11/20 11:32:29 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include "gcmalloc.h"
# include <readline/readline.h>
# include <readline/history.h>

# define TOTAL_KEYWORDS 7
# define MIN_WORD_LENGTH 2
# define MAX_WORD_LENGTH 6
# define MIN_HASH_VALUE 2
# define MAX_HASH_VALUE 9

extern int	g_exit_code;

/*# define malloc(size) \
({ \
	void * ret = malloc(size); \
	if (!ret) \
		fprintf(stderr, "malloc fail at %s:%d failed: %s\n", \
			__FILE__, __LINE__, strerror(errno)); \
	else \
		fprintf(stderr, "malloc at(%p) at %s:%d\n", \
		ret, __FILE__, __LINE__); \
	ret; \
})*/

/*# define gc_free(addr) \
do \
{ \
	fprintf(stderr, "gc_free(%p) at %s:%d\n", \
			addr, __FILE__, __LINE__); \
	free(addr); \
} while (0)
*/
/*# define gc_malloc(size) \
({ \
	void * ret = gc_malloc(size); \
	if (!ret) \
		fprintf(stderr, "gc_malloc fail at %s:%d failed: %s\n", \
			__FILE__, __LINE__, strerror(errno)); \
	else \
		fprintf(stderr, "gc_malloc at(%p) at %s:%d\n", \
		ret, __FILE__, __LINE__); \
	ret; \
})*/

/*# define ft_calloc(elmt_nbr, elmt_size) \
({ \
	void * ret = ft_calloc(elmt_nbr, elmt_size); \
	if (!ret) \
		fprintf(stderr, "malloc fail at %s:%d failed: %s\n", \
			__FILE__, __LINE__, strerror(errno)); \
	else \
		fprintf(stderr, "ft_calloc at(%p) at %s:%d\n", \
		ret, __FILE__, __LINE__); \
	ret; \
})*/

/*# define free(ptr) \
do \
{ \
	fprintf(stderr, "free(%p) at %s:%d\n", \
			ptr, __FILE__, __LINE__); \
	free(ptr); \
} while (0)*/

/*# define close(fd) \
do \
{ \
	fprintf(stderr, "close(%d) at %s:%d\n", \
			fd, __FILE__, __LINE__); \
	close(fd); \
} while (0)*/

/*#define pipe(pipefd) \
({ \
	int ret = pipe(pipefd); \
	if (ret == -1) \
		fprintf(stderr, "pipe(%p) at %s:%d failed: %s\n", \
				pipefd, __FILE__, __LINE__, strerror(errno)); \
	else \
		fprintf(stderr, "pipe("#pipefd") = {%d,%d} at %s:%d\n", \
		pipefd[0], pipefd[1], \
		__FILE__, __LINE__); \
	ret; \
})

# define dup2(fd1, fd2) \
do \
{ \
	fprintf(stderr, "dup2(%d, %d) at %s:%d\n", \
			fd1, fd2, __FILE__, __LINE__); \
	 if (dup2(fd1, fd2) == -1) \
	 	perror("dup2"); \
} while (0)*/

typedef enum e_read_or_write
{
	READ,
	WRITE
}	t_read_or_write;

typedef enum e_redir_or_cmd
{
	REDIR,
	CMD,
}	t_redir_or_cmd;

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
	int			cmd_nbr;
	t_command	*cmd;
	t_env		*env;
	t_list		*pid;
	int			status;
}	t_exec;

typedef struct s_builtin
{
	const char	*key;
	int			(*builtin_func)(t_command *, t_exec *);
}	t_builtin;

void		print_open_fds(const char *where);
void		free_cmd_exec(t_exec *exec, t_command *to_keep);
void		parent(t_command *cmd, t_exec *exec, int depth);
int			verif_and_close(int *fd);
void		ft_error(char *message, int which, int status);
void		free_lst(t_list *lst);
int			lst_size(t_env *env);
char		*this_is_the_path(char **path, char *cmd);
void		return_code(t_exec *exec);
void		close_all(t_command *cmd);
void		double_array_free(char **strs);
int			runner(t_command *cmd, t_exec *exec, int *pipe_fds, int next_out);
void		fork_init(t_exec *exec);
int			struct_init(t_exec *exec, t_command *cmd, char **envp);
void		child(t_exec *exec, t_command *cmd, int next_out);
void		execve_fail(char *path, int status);
char		**lst_to_array(t_env *env);
void		here_doc(t_redir *redir);
int			read_or_write(int read_or_write, t_redir *redir);
void		hold_on(t_list *lst, int *status);
t_builtin	*htable_get(const char *str, size_t len);
int			echo_builtin(t_command *cmd, t_exec *exec);
int			cd_builtin(t_command *cmd, t_exec *exec);
int			env_builtin(t_command *cmd, t_exec *exec);
int			exit_builtin(t_command *cmd, t_exec *exec);
int			export_builtin(t_command *cmd, t_exec *exec);
int			pwd_builtin(t_command *cmd, t_exec *exec);
int			unset_builtin(t_command *cmd, t_exec *exec);
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
