/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thryndir <thryndir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:38:30 by thryndir          #+#    #+#             */
/*   Updated: 2024/09/21 17:40:20 by thryndir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static unsigned int hash(register const char *str, register size_t len)
{
	static unsigned char asso_values[] =
		{
		10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,
		10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,
		10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,
		10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,
		10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10, 5,
		0,10,10,10,10,10,10,10,10,10,0,10,10,10,10,10,10,10,10, 5,
		0,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,
		10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,
		10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,
		10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,
		10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,
		10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,
		10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10
		};
	return len + asso_values[(unsigned char)str[1]];
}

t_builtin *htable_get(const char *str, size_t len)
{
	static t_builtin wordlist[] = 
	{
		{"", NULL}, {"", NULL},
		{"cd", (void *)cd_builtin},
		{"env", (void *)env_builtin},
		{"exit", (void *)exit_builtin},
		{"unset", (void *)unset_builtin},
		{"export", (void *)export_builtin},
		{"", NULL},
		{"pwd", (void *)pwd_builtin},
		{"echo", (void *)echo_builtin}
	};
	if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
		{
			unsigned int key = hash (str, len);
			if (key <= MAX_HASH_VALUE)
				{
					const char *s = wordlist[key].key;
					if (*str == *s && !ft_strcmp (str + 1, s + 1))
						return &wordlist[key];
				}
		}
	return 0;
}
