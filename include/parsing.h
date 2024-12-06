/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 21:46:43 by jgerbaul          #+#    #+#             */
/*   Updated: 2024/12/05 12:09:41 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include "libft.h"
# include "struct.h"

/**
 * Syntax
*/
bool				ft_isspace(char c);
void				quote_count(char c, int *simple_q, int *double_q);
bool				is_symbol_or_nullchar(char c);
bool				check_after_redir(const char **input, char redir);
bool				misplaced_operators(const char *input);
bool				check_invalid_redirection(const char *input);
bool				invalid_operators(const char *input);
bool				unclosed_quotes(const char *input);
int					syntax_errors(const char *input);
int					syntax_error_message(const char *input);

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
void				remove_quotes_from_argv(char **argv);
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
void				set_signal(void);
void				error_message(char *message, int exit_code);
char				*mini_itoa(int nbr);

/**
 * Env swapper
 */
char				*env_substr(char const *str, unsigned int start,
						size_t sublen);
int					get_var_name_len(const char *str);
void				copy_var_value(char *result, int *j, char *var_value);
char				*get_var_value(char *str, int *i, t_env *env);
void				handle_var_expansion(char *str, t_expansion *exp);
int					get_var_len(char *str, int *i, t_env *env);
int					get_expanded_len(char *str, t_env *env);
char				*swap_vars(char *str, t_env *env);
void				swap_arg(char **arg, t_env *env);
void				loop_env_swapper(t_command *cmd, t_env *env);

#endif