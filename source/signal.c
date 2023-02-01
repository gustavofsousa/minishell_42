/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parnaldo <parnaldo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 13:38:39 by parnaldo          #+#    #+#             */
/*   Updated: 2023/02/01 15:49:16 by parnaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	check_eof(t_info *info)
{
	if(!info->prompt)
	{
		write(1, "exit\n", 5);
		exit(0);
	}
}

void	handler(int sig)
{
	if(RL_ISSTATE(RL_STATE_READCMD))
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
	else
		write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	(void) sig;
}

void	init_sig(void)
{
  struct sigaction sa;

  sa.sa_handler = handler;
  sigaction(SIGINT, &sa, NULL);
}
