/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thryndir <thryndir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 21:46:43 by jgerbaul          #+#    #+#             */
/*   Updated: 2024/10/22 11:50:12 by thryndir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdlib.h>
# include <stdbool.h>

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_REDIR_HEREDOC,
	TOKEN_ENV_VAR,
}	t_token_type;

typedef struct s_ast_node
{
	t_token_type		type;
	int					file_type;
	char				**args;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ast_node;

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