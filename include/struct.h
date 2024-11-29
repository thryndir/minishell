/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgerbaul <jgerbaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 22:59:34 by jgerbaul          #+#    #+#             */
/*   Updated: 2024/11/29 23:35:43 by jgerbaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
}	t_redir_type;

typedef struct s_redir
{
	enum e_redir_type	type;
	char				*file;
	int					fd;
	struct s_redir		*next;
}	t_redir;

typedef struct s_command
{
	char				**argv;
	int					argc;
	int					fd_in;
	int					fd_out;
	int					index;
	char				*path;
	struct s_redir		*redirections;
	struct s_command	*next;
}	t_command;

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
}	t_exec;

typedef struct s_builtin
{
	const char	*key;
	int			(*builtin_func)(t_command *, t_exec *);
}	t_builtin;

typedef struct s_expansion
{
	char	*result;
	t_env	*env;
	int		*i;
	int		*j;
}	t_expansion;

#endif