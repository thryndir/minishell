/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgerbaul <jgerbaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 02:09:07 by jgerbaul          #+#    #+#             */
/*   Updated: 2024/12/08 19:46:39 by jgerbaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "gcmalloc.h"


/**
 * This function is an enum selector for the type of
 * redirection we store in the node
 */
enum e_redir_type	get_redir_type(const char *str)
{
	if (str[0] == '<' && str[1] == '<')
		return (REDIR_HEREDOC);
	if (str[0] == '>' && str[1] == '>')
		return (REDIR_APPEND);
	if (str[0] == '<')
		return (REDIR_IN);
	return (REDIR_OUT);
}

/**
 * This function check if the first character of
 * *str is a redirection symbol
 */
bool	is_redirect(const char *str)
{
	return (str[0] == '<' || str[0] == '>');
}

/**
 * Like ft_strdup but allocate memory with the garbage collector
 */
char	*mini_strdup(const char *src)
{
	int		len;
	int		i;
	char	*dest;

	len = ft_strlen(src);
	dest = (char *)gc_malloc((len + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	loop_quote_handler(t_command *cmd)
{
	t_command	*current;
	int			i;
	char		*str;

	current = cmd;
	while (current)
	{
		i = 0;
		while (current->argv[i])
		{
			str = NULL;
			if ((ft_strchr(current->argv[i], '\''))
				|| (ft_strchr(current->argv[i], '"')))
			{
				str = remove_quotes_from_string(current->argv[i]);
				if (str)
				{
					gc_free(current->argv[i]);
					current->argv[i] = str;
				}
			}
			i++;
		}
		current = current->next;
	}
}
