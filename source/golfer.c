/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   golfer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:58:48 by gusousa           #+#    #+#             */
/*   Updated: 2023/03/09 14:49:08 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	do_the_execve(t_info *info, t_list_sent *sent)
{
	char	*right_path;
	char	**right_args;
	int		success;
	int		nbr_child;

	nbr_child = 2;
	success = -1;
	right_path = prepare_path(info, sent);
	right_args = ft_split(sent->content.args, ' ');

	if (info->qtd_sent > 1)
	{
		dup2(sent->content.input, 0);
		dup2(sent->content.output, 1);
	}
	else
		nbr_child = fork();
	if (nbr_child == 0)
	{
		//close_fdes();
		success = execve(right_path, right_args, info->env_cpy);
	}
	//O pai fica esperando com um waitpid, ate executar o comando. Precisa saber o PID do ultimo processo filho.
	/*
	free(right_path);
	while (right_args)
		free((*right_args)++);
	free(right_args);
	*/
	return (success);
}

int	create_forks(t_list_sent **senti, int qtd_pipes)
{
	int			i;
	int			n_sent;
	int			nbr_child;
	int			fildes[2];
	int			success;
	t_list_sent	*sent;

	sent = *senti;
	n_sent = -1;
	i = -1;
	while (++i < qtd_pipes)
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
	nbr_child = 0;
	while (n_sent--)
	{
		nbr_child = fork();
		if (nbr_child == 0)
			break;
		sent = sent->next;
	}
	return (nbr_child);
}

int	count_sentence(t_list_sent *sentence)
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
	int	qtd_pipe;
	int return_execv;

	// Multipiping
	return_execv = -1;
	qtd_pipe = count_sentence(sent) - 1;
	info->qtd_sent = qtd_pipe + 1;
	if (qtd_pipe > 0)
		create_forks(&sent, qtd_pipe);

	if (sent->content.command != no_builtin)
		do_the_builtin(sent->content.command, sent->content.args,
				sent->content.output, info);
	else
		return_execv = do_the_execve(info, sent);
}
