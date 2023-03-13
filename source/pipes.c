/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 19:19:23 by gusousa           #+#    #+#             */
/*   Updated: 2023/03/13 19:47:20 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	open_pipes(t_list_sent **senti, t_info *info)
{
	int			i;
	int			success;
	int			fildes[2];
	t_list_sent	*sent;

	sent = *senti;
	i = 0;
	while (++i < info->qtd_sent)
	{
		success = pipe(fildes);//Primeiro le, segundo escreve.
		if (success == 0)
		{
			if (sent->content.output == 1)
				sent->content.output = fildes[1];
			else
				close (fildes[1]);
			sent = sent->next;
			if (sent == NULL)
				break;
			if (sent->content.input == 0)
				sent->content.input = fildes[0];
			else
				close (fildes[0]);
		}
	}
}

void	config_fd_system(t_list_sent *sent, t_info *info)
{
	dup2(sent->content.input, 0);
	dup2(sent->content.output, 1);
	close_fdes(info);
}

void	wait_children_die(t_info *info)
{
	int		pre_status;
	int		n_sent;

	n_sent = -1;
	pre_status = 0;
	while (++n_sent < info->qtd_sent)
	{
		waitpid(info->nbr_pids[n_sent], &pre_status, 0);
		printf("The son-> %d has finished\n", info->nbr_pids[n_sent]);
		if (WIFEXITED(pre_status))
			g_status = WEXITSTATUS(pre_status);
		if (WIFSIGNALED(pre_status))
			g_status = 128 + WTERMSIG(pre_status);
	}
}

