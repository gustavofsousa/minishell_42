/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   golfer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:58:48 by gusousa           #+#    #+#             */
/*   Updated: 2023/03/10 13:22:20 by gusousa          ###   ########.fr       */
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

	pre_status = 0;
	waitpid(info->last_pid, &pre_status, WUNTRACED);
	if (WIFEXITED(pre_status))
		g_status = WEXITSTATUS(pre_status);
	if (WIFSIGNALED(pre_status))
		g_status = 128 + WTERMSIG(pre_status);
}

int	do_the_execve(t_info *info, t_list_sent *sent)
{
	char	*right_path;
	char	**right_args;
	int		success;
	int		nbr_pid;

	nbr_pid = 0;
	success = 0;
	right_path = prepare_path(info, sent);
	right_args = ft_split(sent->content.args, ' ');

	if (info->qtd_sent == 1)
		nbr_pid = fork();
	if (nbr_pid == 0)
	{
		config_fd_system(sent, info);
		success = execve(right_path, right_args, info->env_cpy);
	}
	else if (nbr_pid > 0)
		wait_children_die(info);
	else
		perror("error in fork");
	freeing_local(right_path, right_args);
	return (success);
}

static void	open_pipes(t_list_sent **senti, t_info *info)
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
				sent->content.output = fildes[1];
				sent = sent->next;
				if (sent == NULL)
					break;
				sent->content.input = fildes[0];
		}
	}
}

void	create_forks(t_list_sent **senti, t_info *info)
{
	int			n_sent;
	int			nbr_pid;
	int			pre_status;

	pre_status = 0;
	open_pipes(senti, info);
	n_sent = -1;
	nbr_pid = 0;
	while (++n_sent < info->qtd_sent)
	{
		nbr_pid = fork();
		info->last_pid = nbr_pid;
		if (nbr_pid == 0)
			break;
		else if (nbr_pid > 0)
		{
			waitpid(info->last_pid, &pre_status, WNOHANG);
			if (WIFEXITED(pre_status))
				g_status = WEXITSTATUS(pre_status);
			if (WIFSIGNALED(pre_status))
				g_status = 128 + WTERMSIG(pre_status);
		}
		else
			perror("error in fork");
		*senti = (*senti)->next;
	}
}

static int	count_sentence(t_list_sent *sentence)
{
	int	len;

	len = 0;
	while (sentence)
	{
		len++;
		sentence = sentence->next;
	}
	return (len);
}

void	golfer(t_list_sent *sent, t_info *info)
{
	int return_execv;
	int	pre_status;

	pre_status = 0;
	return_execv = 0;
	info->qtd_sent = count_sentence(sent);
	if (info->qtd_sent > 1)
		create_forks(&sent, info);
	if (sent != NULL)
	{
		if (sent->content.command != no_builtin)
			do_the_builtin(sent, info);
		else
			return_execv = do_the_execve(info, sent);
		if (return_execv == -1)
		{
			perror("Error in execve");
			//setar gloval do filho.
			// Limpsr as paradas.
		}
	}
	else
	{
		wait_children_die(info);
	}
}
