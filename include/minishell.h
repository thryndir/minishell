/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 17:34:36 by thryndir          #+#    #+#             */
/*   Updated: 2024/09/24 18:41:53 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
	FREE_ENV = 2,
	FREE_P_PATH = 3,
	CLOSE_PIPE = 4,
	FREE_PIPE = 5,
	FREE_CMD = 6,
	FREE_PATH = 7,
	FREE_LST = 8
}	t_error;

typedef enum e_child
{
	NO_PIPE_CHILD,
	FIRST_CHILD,
	MIDDLE_CHILD,
	LAST_CHILD
}	t_child;

typedef struct s_flags
{
	uint8_t _d : 1;
	uint8_t _f : 1;
}	t_flags;

typedef	struct	s_test
{
	int	a;
}	t_test;

typedef struct s_pipex
{
	char		**p_path;
	char		**cmds;
	char		*path;
	int			(*pipe_fd)[2];
	char		*infile;
	char		*outfile;
	int			cmd_nbr;
	bool		pipe;
	t_list		*lst;
	char		**env;
	bool		here_doc;
	int			status;
}	t_pipex;

typedef struct s_builtin
{
	const char* key;
	int (*builtin_func)(t_pipex *);
}	t_builtin;

char		**search_in_env(char **env);
void		pipe_parent(char **argv, int end, t_pipex *pipex);
void		ft_error(char *message, t_pipex *pipex, int which, int status);
char		*this_is_the_path(t_pipex *pipex, char **p_path, char **cmd);
void		free_all(t_pipex *pipex, int which);
void		init_exec(t_pipex *pipex, char *cmd);
void		return_code(t_pipex *pipex);
void		double_array_free(char **strs);
void		runner(int current, t_pipex *pipex, int which);
void		fork_init(t_pipex *pipex);
void		no_pipe_parent(char **argv, int end, t_pipex *pipex);
void		no_pipe_child(t_pipex *pipex);
void		no_pipe_init(t_pipex *pipex, char **argv, int argc);
void		init_pipe_fds(t_pipex *pipex);
void		struct_init(t_pipex *pipex, char **argv, int argc, char **env);
void		last_child(int current, t_pipex *pipex, int (*pipe_fd)[2]);
void		first_child(int current, t_pipex *pipex, int (*pipe_fd)[2]);
void		middle_child(int current, t_pipex *pipex, int (*pipe_fd)[2]);
void		close_pipe(int (*pipe_fd)[2], int cmd_nbr);
void		here_doc(t_pipex *pipex, char *lim);
int			read_or_write(char *file, int read_or_write, t_pipex pipex);
void		here_doc_verif(t_pipex *pipex, int argc, char **argv);
void		hold_on(t_list *lst, int *status);
t_builtin	*htable_get(const char *str, size_t len);
int			echo_builtin(t_pipex *pipex);
int			cd_builtin(t_pipex *pipex);
int			env_builtin(t_pipex *pipex);
int			exit_builtin(t_pipex *pipex);
int			export_builtin(t_pipex *pipex);
int			pwd_builtin(t_pipex *pipex);
int			unset_builtin(t_pipex *pipex);

#endif