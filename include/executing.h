/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:30:43 by lgalloux          #+#    #+#             */
/*   Updated: 2024/12/11 10:34:41 by lgalloux         ###   ########.fr       */
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
# include "struct.h"
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

void		free_cmd_exec(t_exec *exec, t_command *to_keep);
void		parent(t_command *cmd, t_exec *exec, int depth);
int			verif_and_close(int *fd);
void		print_error(char *msg, char *detail, int exit_code);
void		error_and_quit(char *msg, char *detail, int exit_code);
void		free_lst(t_list *lst);
int			lst_size(t_env *env);
char		*find_path(char **path, char *cmd, int *pipe_fds, int next_out);
void		redirect(t_command *cmd, t_exec *exec, int pipe_fds[2],
				int next_out);
char		*last_fd_type(int type, t_command *cmd, t_redir *redir,
				int pipe_fds[2]);
void		double_array_free(char **strs);
void		runner(t_command *cmd, t_exec *exec, int *pipe_fds, int next_out);
void		fork_init(t_exec *exec);
int			struct_init(t_exec *exec, t_command *cmd);
void		child(t_exec *exec, t_command *cmd, int next_out);
void		execve_fail(t_command *cmd);
char		**lst_to_array(t_env *env);
void		here_doc(t_redir *redir);
int			read_or_write(int read_or_write, t_redir *redir);
void		hold_on(t_list *lst);
t_builtin	*htable_get(const char *str, size_t len);
void		echo_builtin(t_command *cmd, t_exec *exec);
void		cd_builtin(t_command *cmd, t_exec *exec);
void		env_builtin(t_command *cmd, t_exec *exec);
void		exit_builtin(t_command *cmd, t_exec *exec);
void		export_builtin(t_command *cmd, t_exec *exec);
void		pwd_builtin(t_command *cmd, t_exec *exec);
void		unset_builtin(t_command *cmd, t_exec *exec);
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
void		redirect_builtin(t_command *cmd, t_exec *exec, int *pipe_fds,
				int next_out);
void		close_prev_open(t_redir *to_comp, t_redir *redir);
void		keep_fd(t_redir *redir, t_command *cmd, int pipe_fds[2],
				int next_out);
void		restore_std(int save_or_restore);

#endif
