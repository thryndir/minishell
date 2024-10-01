#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_word
{
	char  *str;
	char  quote;
	int  has_space;
	struct s_word  *next;
	struct s_word  *prev;
}	t_word;

typedef struct s_cmd
{
	struct s_io		*input;
	struct s_io		*output;
	struct s_word	*tokens;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;


typedef struct s_io
{
	int			io;
	char		*file;
	struct s_io	*next;
	struct s_io	*previous;
}	t_io;

void parser(int ac, char **av, t_cmd *cmd)
{
	int i = 1;
	t_word *token;
	cmd->tokens = NULL;
	cmd->input = NULL;
	cmd->output = NULL;
	while (i < ac)
	{
		token = malloc(sizeof(t_word));
		token->str = av[i];
		token->quote = 0;
		token->has_space = 0;
		token->next = NULL;
		token->prev = NULL;
		if (!cmd->tokens)
			cmd->tokens = token;
		else
		{
			t_word *last = cmd->tokens;
			if (last->next != NULL)
				last = last->next;
			last->next = token;
			token->prev = last;
		}
		i++;
	}
}

void free_token(t_cmd *cmd)
{
	t_word *current = cmd->tokens;
	t_word *next;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	cmd->tokens = NULL;
}


void print_token(t_cmd *cmd)
{
	t_word *current = cmd->tokens;
	while (current != NULL)
	{
		printf("%s\n", current->str);
		current = current->next;
	}
}
int main(int ac, char **av)
{
	t_cmd cmd;
	parser(ac, av, &cmd);
	print_token(&cmd);
	free_token(&cmd);
	return 0;
}
