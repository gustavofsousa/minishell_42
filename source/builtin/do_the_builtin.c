/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_the_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:47:45 by gusousa           #+#    #+#             */
/*   Updated: 2023/03/13 15:42:04 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	do_the_builtin(t_list_sent *sent, t_info *info, int i)
{
	if (info->qtd_sent > 1)
	{
		info->nbr_pids[i] = fork();
		if (info->nbr_pids[i] > 0)
			return (1);
	}
	if (sent->content.command == pwd)
		ft_pwd(sent->content.output);
	else if (sent->content.command == echo)
		ft_echo(sent->content.args, sent->content.output);
	else if (sent->content.command == exiter)
		ft_exit(sent->content.args);
	else if (sent->content.command == env)
		ft_env(info->env_cpy, sent->content.output);
	else if (sent->content.command == unset)
		ft_unset(sent->content.args, info);
	else if (sent->content.command == cd)
		ft_cd(sent->content.args);
	else if (sent->content.command == exporter)
		ft_export(sent->content.args, info);
	printf("My PDI->%d\n", getpid());
	if (info->qtd_sent > 1)
		return (-1);
	return (1);
}

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
				sent->content.output = fildes[1];
				sent = sent->next;
				if (sent == NULL)
					break;
				sent->content.input = fildes[0];
		}
	}
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
