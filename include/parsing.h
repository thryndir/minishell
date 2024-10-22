/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thryndir <thryndir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 21:46:43 by jgerbaul          #+#    #+#             */
/*   Updated: 2024/10/22 17:54:55 by thryndir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdlib.h>
# include <stdbool.h>

// the differents types of nodes
typedef enum e_type {
	NODE_PIPE,
	NODE_CMD,
	NODE_REDIR
}	t_type;

// The differents types of redirections possible
typedef	enum e_redir_type {
	REDIR_IN,//		<
	REDIR_OUT,//	>
	REDIR_APPEND,//	>>
	REDIR_HEREDOC//	<<
}	t_redir_type;

// the structure for the node type pipe
typedef struct s_pipe
{
	t_node	*left;//  the left node
	t_node	*right;// the right node
}	t_pipe;

// the structure for the node type redirection
typedef	struct s_redir
{
	enum e_redir_type	type;//	 the type of the redirection
	char				*file;// the file of the redirection
	struct s_node		*cmd;//  the node type command associated with the redirection
}	t_redir;

// the structure for the node type command
typedef struct s_command
{
	char	*name;//  the name of the command
	char	**args;// the arguments of the command
	char	*path;//  the path to the command
}	t_command;

// the main structure of the node
typedef struct s_node
{
	enum e_type	type;// type of node
	union// union optimize the memory taken by the structure by allowing only
	{//		one node type at the time
		struct s_pipe		pipe;
		struct s_command	cmd;
		struct s_redir		redir;
	} u;
}	t_node;

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

#endif