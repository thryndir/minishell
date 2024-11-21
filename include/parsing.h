/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgerbaul <jgerbaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 21:46:43 by jgerbaul          #+#    #+#             */
/*   Updated: 2024/11/21 18:44:22 by jgerbaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include "libft.h"

///////////////////////TEMPORAIRE/////////////////////
// The differents types of redirections possible
typedef enum e_redir_type
{
	REDIR_IN,//		<
	REDIR_OUT,//	>
	REDIR_APPEND,//	>>
	REDIR_HEREDOC,//<< 
	REDIR_NULL, // needed to compile with -Werror
}	t_redir_type;

typedef struct s_redir
{
	enum e_redir_type	type;//	 the type of the redirection
	char				*file;// the file of the redirection
	int					fd;//	 the fd of the file
	struct s_redir		*next;// a pointer ot the next node
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
/////////////////////////////////////////////////////

/**
 * PARSING FUNCTIONS
*/

/**
 * Syntax
*/
bool				ft_isspace(char c);
void				quote_count(char c, int *simple_q, int *double_q);
bool				is_symbol_or_nullchar(char c);
bool				check_after_redir(const char **input, char redir);
bool				syntax_checker(const char *input);
bool				misplaced_operators(const char *input);
bool				check_invalid_redirection(const char *input);
bool				invalid_operators(const char *input);
bool				unclosed_quotes(const char *input);
int					syntax_errors(const char *input);

/**
 * Tokenizer
*/
bool				is_quote(char c);
bool				is_symbol(char c);
bool				is_double_symbol(const char *str, int i);
bool				count_quoted_word(const char *str, int *i);
bool				count_regular_word(const char *str, int *i);
int					count_word(const char *str, int *i);
int					mini_strnbr(const char *str);
int					mini_charnbr(const char *str);
void				mini_malloc_fail(char **strs, int j);
char				*extract_quoted_word(const char *str, int *i, int len);
char				*extract_regular_word(const char *str, int *i, int len);
char				*extract_word(const char *str, int *i, int *status);
char				**mini_str_to_array(char **strs, const char *str);
char				**ft_mini_split(char const *str);

void				free_redirs(t_redir *redir);
void				free_command_argv(char **argv);
void				free_commands(t_command *cmd);
t_redir				*init_redir(void);
t_command			*init_command(void);
int					add_redir(t_command *cmd, t_redir *new_redir);
int					add_command(t_command **cmd_list, t_command *new_cmd);
int					count_command_argv(char **input, int index);
int					copy_arg(t_command *cmd, char **input,
						int *start, int *arg_index);
int					handle_argv(t_command *cmd, char **input,
						int start, int count);
t_redir				*create_redir(const char *op, const char *file);
int					process_one_redirection(t_command *cmd, char **input,
						int *i, int start);
int					process_redirections(t_command *cmd, char **input,
						int start, int count);
char				*mini_strdup(const char *src);
bool				is_redirect(const char *str);
enum e_redir_type	get_redir_type(const char *str);
t_command			*parse_command(char **input, int *index);
t_command			*parse_input(char **input);

#endif