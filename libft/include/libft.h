/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:59:46 by lgalloux          #+#    #+#             */
/*   Updated: 2024/11/20 12:22:09 by lgalloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <unistd.h>
# include <stdbool.h>
# include <fcntl.h>
# include "gcmalloc.h"
# include <stdio.h>
# include <limits.h>
# include <stdbool.h>

/******************************************************************************/
/*                                                                            */
/* Structures                                                                 */
/*                                                                            */
/******************************************************************************/

typedef struct s_list
{
	int				data;
	struct s_list	*next;
}	t_list;

/******************************************************************************/
/*                                                                            */
/* Macro                                                                      */
/*                                                                            */
/******************************************************************************/

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define MIN "0123456789abcdef"
# define MAJ "0123456789ABCDEF"

/******************************************************************************/
/*                                                                            */
/* CType                                                                      */
/*                                                                            */
/******************************************************************************/

/**
 * @brief Tells wheter or not if `c` is a space
 * 
 * @param c the char we are comparing
 * @return int return 1 if `c` is a space, 0 in the other case
 */
bool			ft_isspace(char c);

/**
 * @brief Tells whether or not `c` is a letter.
 * @param c A character.
 * @return Whether or not `c` is a letter.
 */
int				ft_isalpha(int c);

/**
 * @brief Tells whether or not `c` is a digit.
 * @param c A character.
 * @return Whether or not `c` is a digit.
 */
int				ft_isdigit(int c);

/**
 * @brief Tells whether or not `c` is a letter or a digit.
 * @param c A character.
 * @return Whether or not `c` is a letter or a digit.
 */
int				ft_isalnum(int c);

/**
 * @brief Tells whether or not `c` is an ascii character.
 * @param c A character.
 * @return Whether or not `c` is an ascii character.
 */
int				ft_isascii(int c);

/**
 * @brief Tells whether or not `c` is printable.
 * @param c A character.
 * @return Whether or not `c` is printable.
 */
int				ft_isprint(int c);

/**
 * @brief If `c` is a letter, converts it to uppercase.
 * @param c a character.
 * @return The transformes character.
 */
int				ft_toupper(int c);

/**
 * @brief If `c` is a letter, converts it to lowercase.
 * @param c a character.
 * @return The transformes character.
 */
int				ft_tolower(int c);

/******************************************************************************/
/*                                                                            */
/* Get_next_line                                                              */
/*                                                                            */
/******************************************************************************/

/**
 * @brief Get the next line of the file 'fd'
 * 
 * @param fd the file who are open
 * @return char* the next line of the file
 */
char			*get_next_line(int fd);

/**
 * @brief Concatenate `src` to `dst`. Takes the full `size` of `dst`
 * and guarantee to NUL-terminate the result (as long as there is at least one
 * byte free in `dst`). Note that a byte for the NUL should be included in
 * `size`. Can only operate on true “C” strings. This means that both `src`
 * and `dst` must be NUL-terminated. Appends the NUL-terminated string `src` to
 * the end of `dst`. It will append at most `size - ft_strlen(dst) - 1` bytes,
 * NUL-terminating the result. This function is the same as strlcat but is has
 * been modified to be executed specialy with get_next_line
 * 
 * @param dst A pointer to a memory area.
 * @param src A string.
 * @param size The length of the string `ft_strlcat` tries to create.
 * @return size_t The initial length of `dest` plus the length of `src`.
 */
size_t			ft_backcat(char *dst, const char *src, size_t size);

/**
 * @brief Allocates (with malloc(3)) and returns a new string, which is the
 * result of the concatenation of `s1` and `s2`.  This function is the same
 * as strlcat but is has been modified to be executed specialy with get_next_line
 * 
 * @param str1 The prefix string.
 * @param str2 The suffix string.
 * @return char* The new string or `NULL` if the allocation fails.
 */
char			*ft_backjoin(const char *str1, const char *str2);

/**
 * @brief Create a new string by removing the characters after '\n'
 * 
 * @param buffer the string of the len buffer_size which contains
 * the buffer from get_next_line
 */
void			ft_clean_line(char *buffer);

/**
 * @brief calls ft_clean_line, frees str and return NULL or str if str != NULL
 * 
 * @param str a string which contains buffer before the '\n'
 * @param buffer a string which contains all the buffer from get_next_line
 * @return char* a string which is the line of the file or NULL if it's the end.
 */
char			*ft_end_of_line(char *str, char *buffer);

/******************************************************************************/
/*                                                                            */
/* printf                                                                     */
/*                                                                            */
/******************************************************************************/

/**
 * @brief print character in the fd
 * 
 * @param format an 'char *' when we have '%' the next charactere 
 * call the other params
 * 
 * @param fd precise in which file descriptor you want to write
 * 
 * @param ... number of variables that vary
 * @return int the numbers of the character who are printed
 */
int				ft_dprintf(int fd, const char *format, ...);

/**
 * @brief print the characters sent by format in the fd 1
 * @param ... number of variables that vary
 * @return int the numbers of the character who are printed
 */
int				ft_printf(const char *format, ...);

/**
 * @brief print an int and give his length
 * 
 * @param fd precise in which file descriptor you want to write
 * 
 * @param nb number who need to be printed
 * @return int the number of caractere who are printed
 */
int				ft_printnbr(int nb, int fd);

/**
 * @brief print an int and give his length in base 'base'
 * 
 * @param fd precise in which file descriptor you want to write
 * 
 * @param base an number base
 * @param nb number who need to be printed in base 'base'
 * @return int the number of caractere who are printed
 */
int				ft_printunbr_base(unsigned int nb, int fd, char *base);

/**
 * @brief print an pointer address and give his length in base 'base'
 * 
 * @param fd precise in which file descriptor you want to write
 * 
 * @param address a pointer
 * @return int the number of caracter in the address
 */
int				ft_printptr(void *address, int fd);

/**
 * @brief print a char and return 1
 * 
 * @param fd precise in which file descriptor you want to write
 * 
 * @param c the char who are printed
 * @return int 1
 */
int				ft_printchar(char c, int fd);

/**
 * @brief print an str and return is length
 * 
 * @param fd precise in which file descriptor you want to write
 * 
 * @param str the str who are printed
 * @return int the lenght of the str
 */
int				ft_printstr(char *str, int fd);

/******************************************************************************/
/*                                                                            */
/* String                                                                     */
/*                                                                            */
/******************************************************************************/

/**
 * @brief Calculates the length of `str`.
 * @param str A string.
 * @return The length of `str`.
 */
size_t			ft_strlen(const char *str);

/**
 * @brief Tells wheter or not if `word` is in `str`
 * 
 * @param str the string where we are searching
 * @param word the word we are searching in the string
 * @param len the len of the word
 * @return int return 1 if the word is in str, 0 otherwise
 */
int				ft_is_word_in(const char *str, const char *word, int len);

/**
 * @brief Compares with the lexical order the `n` first characters of `s1`
 * and `s2`.
 * @param s1 A string.
 * @param s2 A string.
 * @return The lexical order of the two string.
 */
int				ft_strcmp(const char *s1, const char *s2);

/**
 * @brief Sets `n` bytes of `s` to `c`.
 * @param s A pointer to a memory area.
 * @param c A byte.
 * @param n The ammount of bytes to set to `c`.
 * @return The `s` pointer.
 */
void			*ft_memset(void *s, int c, size_t n);

/**
 * @brief Writes `n` zeros ('\0') to `s`.
 * @param s A pointer to a memory area.
 * @param n The ammount of bytes to set to zero.
 */
void			ft_bzero(void	*s, size_t	n);

/*!
 * @brief Copies `n` bytes of `src` to `dest`. The memory areas mus not overlap.
 * ft_memmove will not orverlap
 * @param dest A pointer to a memory area.
 * @param src A pointer to a memory area.
 * @param n The ammount of bytes to copy.
 * @return The `dest` pointer.
 */
void			*ft_memcpy(void	*dest, const void	*src, size_t	n);

/**
 * @brief copies `n` bytes from memory area `src` to memory area `dst`.
 * The memory areas may overlap: copying takes place as though the bytes in
 * `src` are first copied into a temporary array that does not overlap `src`
 * or `dst`, and the bytes are then copied from the temporary array to `dst`.
 * @param dest A pointer to a memory area.
 * @param src A pointer to a memory area.
 * @param n The ammount of bytes to copy.
 * @return The `dst` pointer.
 */
void			*ft_memmove(void *dest, const void *src, size_t n);

/**
 * @brief copies 'src' to 'dest'
 * 
 * @param dest A pointer to a memory area.
 * @param src A string.
 * @return char* the string dest.
 */
char			*ft_strcpy(char *dest, char *src);

/**
 * @brief Copies `src` to `dst`. Takes the full `size` of `dst` and guarantee
 * to NULL-terminate the result (as long as `size` is larger than 0). Note that a
 * byte for the NULL should be included in `size`. Can only operate on true "C"
 * strings. `src` must be NULL-terminated. Copies up to `size - 1` characters
 * from `src` to `dst`, NULL-terminating the result.
 * @param dst A pointer to a memory area.
 * @param src A string.
 * @param size The length of the string `ft_strlcopy` tries to create.
 * @return The length of `src`.
 */
size_t			ft_strlcpy(char	*dst, const char	*src, size_t size);

/**
 * @brief Concatenate `str` to `dst`. Takes the full `size` of `dst`
 * and guarantee to NUL-terminate the result (as long as there is at least one
 * byte free in `dst`). Note that a byte for the NUL should be included in
 * `size`. Can only operate on true “C” strings. This means that both `src`
 * and `dst` must be NUL-terminated. Appends the NUL-terminated string `src` to
 * the end of `dst`. It will append at most `size - ft_strlen(dst) - 1` bytes,
 * NUL-terminating the result.
 * @param dest A pointer to a memory area.
 * @param src A string.
 * @param size The length of the string `ft_strlcat` tries to create.
 * @return The initial length of `dest` plus the length of `src`.
 */
size_t			ft_strlcat(char *dest, const char *src, size_t size);

/**
 * @brief Returns a pointer to the first occurence of `c` in `str` if it exists,
 * `NULL` otherwise.
 * @param str A string.
 * @param c A character.
 * @return A pointer to the first occurence of `c` in `str` if it exists,
 * `NULL` otherwise.
 */
char			*ft_strchr(const char *str, int c);

/**
 * @brief Returns a pointer to the last occurence of `c` in `str` if it exists,
 * `NULL` otherwise.
 * @param str A string.
 * @param c A character.
 * @return A pointer to the last occurence of `c` in `str` if it exists,
 * `NULL` otherwise.
 */
char			*ft_strrchr(const char *str, int c);

/**
 * @brief Compares with the lexical order the `n` first characters of `s1`
 * and `s2`.
 * @param s1 A string.
 * @param s2 A string.
 * @param n The max ammount of characters to compare.
 * @return The lexical order of the two string.
 */
int				ft_strncmp(const char *s1, const char *s2, size_t n);

/**
 * @brief Compares with the lexical order the `n` first bytes of `s1`
 * and `s2`.
 * @param s1 A memory area.
 * @param s2 A memory area.
 * @param n The max ammount of bytes to compare.
 * @return The lexical order of the two memory area.
 */
int				ft_memcmp(const void *s1, const void *s2, size_t n);

/**
 * @brief Returns a pointer to the first occurence of the byte `c` in `ptr` if
 * it exists, `NULL` otherwise.
 * @param ptr A memory area.
 * @param c A byte.
 * @return A pointer to the first occurence of the byte `c` in `ptr` if it
 * exists, `NULL` otherwise.
 */
void			*ft_memchr(const void *ptr, int c, size_t n);

/**
 * @brief Locates the first occurrence of the null-terminated string `little`
 * in the string `big`, where no more than `len` characters are searched.
 * Characters that appear after a `\0` are not searched.
 * @param big The string where we are searching.
 * @param little The searched string.
 * @param len The size of the search in `big`.
 * @return If `little` is an empty string, `big` is returned; if `little` occurs
 * nowhere in `big`, `NULL` is returned; otherwise a pointer to the first
 * character of the first occurrence of `little` is returned.
 */
char			*ft_strnstr(const char *big, const char *little, size_t len);

/**
 * @brief Allocates (with malloc(3)) and returns a copy of `str`.
 * @param str A string.
 * @return A copy of `str`.
 */
char			*ft_strdup(const char *str);

/**
 * @brief Allocates (with malloc(3)) and returns a substring from the
 * string `str`. The substring begins at index `start` and is of maximum
 * size `len`.
 * @param str The string from which to create the substring.
 * @param start The start index of the substring in the string `str`.
 * @param len The maximum length of the substring.
 * @return The substring or `NULL` if the allocation fails.
 */
char			*ft_substr(char const *str, unsigned int start, size_t len);

/**
 * @brief Allocates (with malloc(3)) and returns a new string, which is the
 * result of the concatenation of `s1` and `s2`.
 * @param s1 The prefix string.
 * @param s2 The suffix string.
 * @return The new string or `NULL` if the allocation fails.
 */
char			*ft_strjoin(char const *s1, char const *s2);

/**
 * @brief Allocates (with malloc(3)) and returns a copy of `str` with the
 * characters specified in `set` removed from the beginning and the end of the
 * string.
 * @param str The string to be split.
 * @param set The delimiter character.
 * @return The array of new strings resulting from the split or `NULL` if the
 * allocation fails.
 */
char			*ft_strtrim(char const *str, char const *set);

/**
 * @brief Allocates (with malloc(3)) and returns an array of strings obtained by
 * splitting `s` using the character `c` as a delimiter.
 * The array must end with a `NULL` pointer.
 * @param s The string to be split.
 * @param c The delimiter character.
 * @return The array of new strings resulting from the split or `NULL` if the
 * allocation fails.
 */
char			**ft_split(char const *s, char c);

/**
 * @brief Allocates (with malloc(3)) and returns a string representing the
 * integer received as an argument. Negative numbers must be handled.
 * @param n The integer to convert.
 * @return The string representing the integer or `NULL` if the allocation
 * fails.
 */
char			*ft_itoa(int n);

/**
 * @brief Applies the function `f` to each character of the string `str`, and
 * passing its index as first argument to create a new string (with malloc(3))
 * resulting from successive applications of `f`.
 * @param str The string on which to iterate.
 * @param f The function to apply to each character.
 * @return The string created from the successive applications of `f`. Returns
 * `NULL` if the allocation fails.
 */
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));

/**
 * @brief Applies the function `f` on each character of the string `str`,
 * passing its index as first argument. Each character is passed by address
 * to `f` to be modified if necessary.
 * @param str The string on which to iterate.
 * @param f The function to apply to each character.
 */
void			ft_striteri(char *str, void (*f)(unsigned int, char*));

/******************************************************************************/
/*                                                                            */
/* Stdlib                                                                     */
/*                                                                            */
/******************************************************************************/

/**
 * @brief Converts the initial portion of the string pointed to by `str` to an
 * integer.
 * @param str The string to be converted.
 * @return The converted value.
 */
long long int	ft_atolli(const char *str);

/**
 * @brief Converts the initial portion of the string pointed to by `str` to an
 * unsigned long long integer.
 * @param str The string to be converted.
 * @return The converted value.
 */

size_t			ft_atoull(const char *str);

/**
 * @brief Allocates memory for an array of `nmemb` elements of size bytes each
 * and returns a pointer to the allocated memory. The memory is set to zero. 
 * If `nmemb` or `size` is 0, then calloc() returns either NULL, or a unique
 * pointer value that can later be successfully passed to free(). If the
 * multiplication of `nmemb` and `size` would result in integer overflow, then
 * calloc() returns `NULL` and sets `errno` to `EINOMEM`.
 * @param nmemb The number of elements if the array.
 * @param size The size in bytes of each element.
 * @return Return a pointer to the allocated memory or NULL if case of error.
 */
void			*ft_calloc(size_t nmemb, size_t size);

/**
 * @brief Allocates memory from the 'ptr' to the size 'size', if the 'ptr' 
 * are allocated it's a simple malloc otherwise the fonction will 
 * allocated size from the start of the array 'ptr'.
 * @param ptr the start of the memory.
 * @param size The numbers of elements.
 * @return Return a pointer to the allocated memory or NULL if case of error.
 */
void			*ft_realloc(void *ptr, size_t newsize);

/******************************************************************************/
/*                                                                            */
/* IO                                                                         */
/*                                                                            */
/******************************************************************************/

/**
 * @brief Outputs the character `c` to the given file descriptor.
 * @param c The character to output.
 * @param fd The file descriptor on which to write.
 */
void			ft_putchar_fd(char c, int fd);

/**
 * @brief Outputs the string `str` to the given file descriptor.
 * @param str The string to output.
 * @param fd The file descriptor on which to write.
 */
void			ft_putstr_fd(char *str, int fd);

/**
 * @brief Outputs the string `str` to the given file descriptor followed by a
 * newline.
 * @param str 
 * @param fd 
 */
void			ft_putendl_fd(char *str, int fd);

/**
 * @brief Outputs the signed integer `n` in base 'base' to
 * void	ft_putchar_fd(char c, int fd)
 * @param n The integer to output.
 * @param base the base into which the number is transformed .
 * @param fd The file descriptor on which to write.
 */
void			ft_putnbr_base_fd(size_t n, char *base, int fd);

/**
 * @brief Outputs the signed integer `nbr` to the given file descriptor.
 * @param n The integer to output.
 * @param fd The file descriptor on which to write.
 */
void			ft_putnbr_fd(int nbr, int fd);

/**
 * @brief Outputs the integer `nbr` to the stamdard output.
 * @param nbr The integer to output.
 */
void			ft_putnbr(int nbr);

/******************************************************************************/
/*                                                                            */
/* Linked list                                                                */
/*                                                                            */
/******************************************************************************/

/**
 * @brief Allocates (with malloc(3)) and returns a new node. The member variable
 * `content` is initialized with the value of the parameter `content`.
 * The variable `next` is initialized to `NULL`.
 * @param data The content to create the node with.
 * @return The new node.
 */
t_list			*ft_lstnew(int data);

/**
 * @brief Adds the node `new` at the beginning of `list`.
 * @param list The address of a pointer to the first link of a list.
 * @param new The address of a pointer to the node to be added to the list.
 */
void			ft_lstadd_front(t_list **lst, t_list *new);

/**
 * @brief Counts the number of nodes in a list.
 * @param list The beginning of the list.
 * @return The length of the list.
 */
int				ft_lstsize(t_list *list);

/**
 * @brief Returns the last node of the list.
 * @param list The beginning of the list.
 * @return Last node of the list.
 */
t_list			*ft_lstlast(t_list *list);

/**
 * @brief Adds the node `new` at the end of the list.
 * @param list The address of a pointer to the first link of a list.
 * @param new The address of a pointer to the node to be added to the list.
 */
void			ft_lstadd_back(t_list **list, t_list *new);

/**
 * @brief Takes as a parameter a node and frees the memory of the node’s content
 * using the function `del_fun` given as a parameter and free the node. The
 * memory of `next` must not be freed.
 * @param list The node to free.
 * @param del_fun The address of the function used to delete the content.
 */
void			ft_lstdelone(t_list *lst, int (*del)(int));

/**
 * @brief Deletes and frees the given node and every successor of that node,
 * using the function `del_fun` and free(3). Finally, the pointer to the list
 * must be set to `NULL`.
 * @param list The address of a pointer to a node.
 * @param del_fun The address of the function used to delete the content of the
 * node.
 */
void			ft_lstclear(t_list **lst, int (*del)(int));

/**
 * @brief Iterates the list `list` and applies the function `f` on the content
 * of each node.
 * @param list The address of a pointer to a node.
 * @param f The address of the function used to iterate on the list.
 */
void			ft_lstiter(t_list *lst, void (*f)(int));

/**
 * @brief Iterates the list `list` and applies the function `f` on the content of
 * each node. Creates a new list resulting of the successive applications of the
 * function `f`. The `del_fun` function is used to delete the content of a node
 * if needed.
 * @param list The address of a pointer to a node.
 * @param f The address of the function used to iterate on the list.
 * @param del_fun The address of the function used to delete the content of a
 * node if needed.
 * @return The new list or `NULL` if the allocation fail.
 */
t_list			*ft_lstmap(t_list *lst, int (*f)(int), int (*del)(int));

/******************************************************************************/
/*                                                                            */
/* Security                                                                   */
/*                                                                            */
/******************************************************************************/

#endif