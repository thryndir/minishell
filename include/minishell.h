#ifndef MINISHELL_H
#define MINISHELL_H
#include <stdint.h>

typedef struct s_flags
{
	uint8_t _d : 1;
	uint8_t _f : 1;
}	t_flags;

typedef	struct	s_test
{
	int	a;
}	t_test;

#endif