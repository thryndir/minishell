/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgerbaul <jgerbaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 00:40:38 by jgerbaul          #+#    #+#             */
/*   Updated: 2024/11/26 19:07:28 by jgerbaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executing.h"
#include <readline/readline.h>
#include <stdio.h>

void	control_c_function(int	temp)
{
	(void)temp;
	rl_replace_line("", 0);
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
}

void	set_signal(void)
{
	signal(SIGINT, control_c_function);
	signal(SIGQUIT, SIG_IGN);
}


/*
#include <unistd.h>
int	main(void)
{

	set_signal();

	while (1)
	{
		sleep(1);
	}
//test it by using Ctrl + C and it will display 
//a new line, just like bash shell do
	return (0);
}

//Pressing Ctrl+\ in a bash shell triggers the SIGQUIT
//Pressing Ctrl+D triggers the SIGEOF

*/