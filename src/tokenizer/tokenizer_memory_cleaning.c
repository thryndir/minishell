/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_memory_cleaning.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgerbaul <jgerbaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 01:23:47 by jgerbaul          #+#    #+#             */
/*   Updated: 2024/11/09 01:39:55 by jgerbaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/**
 * This function free the redir node and it's member
 * also closing any fd that could be open
 */
void	free_redirs(t_redir *redir)
{
	t_redir	*temp;

	while (redir)
	{
		temp = redir->next;
		if (redir->file)
			free(redir->file);
		if (redir->fd > 2)
			close(redir->fd);
		free(redir);
		redir = temp;
	}
}

/**
 * This function free the args member of the command node
 */
void	free_command_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

/**
 * This function free the command node
 */
void	free_commands(t_command *cmd)
{
	t_command	*temp;

	while (cmd)
	{
		temp = cmd->next;
		if (cmd->name)
			free(cmd->name);
		if (cmd->path)
			free(cmd->path);
		if (cmd->args)
			free_command_args(cmd->args);
		if (cmd->fd_in > 2)
			close(cmd->fd_in);
		if (cmd->fd_out > 2)
			close(cmd->fd_out);
		free_redirs(cmd->redirections);
		free(cmd);
		cmd = temp;
	}
}
