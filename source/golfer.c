/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   golfer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:58:48 by gusousa           #+#    #+#             */
/*   Updated: 2023/03/10 18:16:52 by gusousa          ###   ########.fr       */
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
		waitpid(info->nbr_pids[n_sent], &pre_status, WUNTRACED);
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
	int		nbr_pid;

	nbr_pid = 0;
	right_path = prepare_path(info, sent);
	right_args = ft_split(sent->content.args, ' ');

	if (info->qtd_sent == 1)
		nbr_pid = fork();
	if (nbr_pid == 0)
	{
		printf("My command->%s\tinput->%d\t output%d\n", sent->content.args, sent->content.input, sent->content.output);
		config_fd_system(sent, info);
		execve(right_path, right_args, info->env_cpy);
			perror("Error in execve");
		return (-1);
	}
	else if (nbr_pid > 0)
		wait_children_die(info);
	else if (nbr_pid == -1)
		perror("error in fork unico");
	printf("soh o pai\n");
	freeing_local(right_path, right_args);
	return (0);
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

	info->nbr_pids = malloc (sizeof(int) * info->qtd_sent);
	open_pipes(senti, info);
	n_sent = -1;
	nbr_pid = 0;
	while (++n_sent < info->qtd_sent)
	{
		nbr_pid = fork();
		info->nbr_pids[n_sent] = nbr_pid;
		if (nbr_pid == 0)
			break;
		else if (nbr_pid == -1)
			perror("error in fork multiplo");
		*senti = (*senti)->next;
	}
	wait_children_die(info);
}

void	run_sentence()
{
// Tentar o waipid( -1, ... , ...);
	while(sent)
	{
	// Execve chama fork sempre dentro dele
	// O builtin verifica a qtd_sent
	// E dah fork ou nao.
	sent = sesnt->next.
	}
	wait_child_die();
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

int	golfer(t_list_sent *sent, t_info *info)
{
	info->qtd_sent = count_sentence(sent);
	if (info->qtd_sent > 1)//entra nas func
		create_forks(&sent, info);//some
	if (sent != NULL)//some
	{
		if (sent->content.command != no_builtin)//entra na run_sent
			do_the_builtin(sent, info);
		else
		{
			if (do_the_execve(info, sent) == -1)
				{
					// olhar o errno (do execve) e setar a global de acordo.
					g_status = 127;
					return (-1);
					// Limpsr as paradas.
				}
		}
	}
	return (0);
}
