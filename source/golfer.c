/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   golfer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:58:48 by gusousa           #+#    #+#             */
/*   Updated: 2023/03/13 15:12:57 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
		waitpid(-2 , &pre_status, WUNTRACED);
			if (WIFEXITED(pre_status))
				g_status = WEXITSTATUS(pre_status);
			if (WIFSIGNALED(pre_status))
				g_status = 128 + WTERMSIG(pre_status);
	}
}

int	do_the_execve(t_info *info, t_list_sent *sent)
{
	char	*right_path;
	char	**right_args;

	right_path = prepare_path(info, sent);
	right_args = ft_split(sent->content.args, ' ');

	config_fd_system(sent, info);
	if (fork() == 0)
	{
		execve(right_path, right_args, info->env_cpy);
		perror("Error in execve");
		return (-1);
	}
	freeing_local(right_path, right_args);
	return (0);
}

int	golfer(t_list_sent **sent, t_info *info)
{
	info->qtd_sent = count_sentence(*sent);
	open_pipes(sent, info);
	while (*sent)
	{
		if ((*sent)->content.command != no_builtin)
		{
			do_the_builtin(*sent, info);
		}
		else
		{
			if (do_the_execve(info, *sent) == -1)
				{
					// olhar o errno (do execve) e setar a global de acordo.
					g_status = 127;
					return (-1);
					// Limpar as paradas.
				}
		}
		*sent = (*sent)->next;
	}
	wait_children_die(info);
	*sent = info->head;
	return (0);
}
