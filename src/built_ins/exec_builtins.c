

#include <minishell.h>

static unsigned int hash(const char *str, size_t len)
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
		printf("%ld", len + asso_values[(unsigned char)str[1]]);
	return len + asso_values[(unsigned char)str[1]];
}

t_builtin *htable_get(const char *str, size_t len)
{
	static t_builtin wordlist[] = 
	{
		{"", NULL}, {"", NULL},
		{"cd", cd_builtin},
		{"env", env_builtin},
		{"exit", exit_builtin},
		{"unset", unset_builtin},
		{"export", export_builtin},
		{"", NULL},
		{"pwd", pwd_builtin},
		{"echo", echo_builtin}
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
