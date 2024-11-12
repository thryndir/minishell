/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgerbaul <jgerbaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 21:46:43 by jgerbaul          #+#    #+#             */
/*   Updated: 2024/11/12 01:38:17 by jgerbaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdlib.h>
# include <stdbool.h>

///////////////////////TEMPORAIRE/////////////////////
// The differents types of redirections possible
typedef	enum e_redir_type {
	REDIR_IN,//		<
	REDIR_OUT,//	>
	REDIR_APPEND,//	>>
	REDIR_HEREDOC,//<< 
}	t_redir_type;

typedef	struct s_redir
{
	enum e_redir_type	type;//	 the type of the redirection
	char				*file;// the file of the redirection
	int					fd;//	 the fd of the file
	struct s_redir		*next;// a pointer ot the next node
}	t_redir;

typedef struct s_command
{
	char				*name;//  		the name of the command
	char				**args;//		the arguments of the command
	int					argc;//			the number of arguments for the command
	int					fd_in;//		the fd_in of the command
	int					fd_out;//		the fd_out of the command
	int					index;//		the index of the command in the chained list
	char				*path;// 		the path to the command
	struct s_redir		*redirections;// a chained list of the redirection of the command
	struct s_command	*next;
}	t_command;
/////////////////////////////////////////////////////

/**
 * PARSING FUNCTIONS
*/

/**
 * Syntax
*/
bool		ft_isspace(char c);
void		quote_count(char c, int *simple_q, int *double_q);
bool		is_symbol_or_nullchar(char c);
bool		check_after_redir(const char **input, char redir);
bool		misplaced_operators(const char *input);
bool		check_invalid_redirection(const char *input);
bool		invalid_operators(const char *input);
bool		unclosed_quotes(const char *input);
bool		syntax_errors(const char *input);

/**
 * Tokenizer
*/
bool		is_quote(char c);
bool		is_symbol(char c);
bool		is_double_symbol(const char *str, int i);
bool		count_quoted_word(const char *str, int *i);
bool		count_regular_word(const char *str, int *i);
int			count_word(const char *str, int *i);
int			ft_strnbr(const char *str);
int			ft_charnbr(const char *str);
void		ft_malloc_fail(char **strs, int j);
char		*extract_quoted_word(const char *str, int *i, int len);
char		*extract_regular_word(const char *str, int *i, int len);
char		*extract_word(const char *str, int *i, int *status);
char		**ft_str_to_array(char **strs, const char *str);
char		**ft_mini_split(char const *str);

void		free_redirs(t_redir *redir);
void		free_command_args(char **args);
void		free_commands(t_command *cmd);
t_redir		*init_redir(void);
t_command	*init_command(void);
int			add_redir(t_command *cmd, t_redir *new_redir);
int			add_command(t_command **cmd_list, t_command *new_cmd);


#endif