/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thryndir <thryndir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:56:47 by lgalloux          #+#    #+#             */
/*   Updated: 2024/12/09 14:15:59 by thryndir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"

int	get_cmd_nbr(t_command *cmd)
{
	t_command	*current;
	t_redir		*redir;
	int			cmd_nbr;

	cmd_nbr = 0;
	current = cmd;
	while (current)
	{
		redir = current->redirections;
		if (redir && redir->type == REDIR_HEREDOC)
		{
			here_doc(redir);
			
		}
		current->index = cmd_nbr;
		current = current->next;
		cmd_nbr++;
	}
	return (cmd_nbr);
}

int	struct_init(t_exec *exec, t_command *cmd)
{
	exec->cmd_nbr = get_cmd_nbr(cmd);
	exec->pid = NULL;
	return (0);
}

void	here_doc(t_redir *redir)
{
	char		*str;
	char		*lim;
	int			fd;

	lim = redir->file;
	redir->file = "/tmp/temp";
	fd = read_or_write(WRITE, redir);
	if (fd == -1)
		print_error("here_doc failed", strerror(errno), errno);
	redir->type = REDIR_IN;
	while (1)
	{
		str = readline("heredoc :");
		if (str == NULL || !ft_strcmp(str, lim))
			break ;
		write(fd, str, ft_strlen(str));
		gc_free(str);
		write(fd, "\n", 1);
	}
	gc_free(str);
	verif_and_close(&fd);
}
