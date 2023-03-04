/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   golfer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:58:48 by gusousa           #+#    #+#             */
/*   Updated: 2023/03/04 09:58:08 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
void	create_forks(t_sentence *sent, int qtd_sent)
{
	int	nbr_child;

	nbr_child = 0;
	while (qtd_sent--)
	{
		//pipe();
		nbr_child = fork();
	}
}

int	count_sentence(t_sentence *sentence)
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
*/

void	golfer(t_list_sent *sent, t_info *info)
{
/*
	int	qtd_sent;

	// Multipiping
	qtd_sent = count_sentence(sent);
	if (qtd_sent > 1)
		create_forks(sent, qtd_sent);
*/

	//Escolher comando
	if (!ft_strncmp(sent->content.command, "pwd", ft_strlen(sent->content.command)))
		ft_pwd();
	else if (!ft_strncmp(sent->content.command, "echo", ft_strlen(sent->content.command)))
		ft_echo(sent->content.args, sent->content.output);
	else if (!ft_strncmp(sent->content.command, "exit", ft_strlen(sent->content.command)))
		ft_exit(sent->content.args);
	else if (!ft_strncmp(sent->content.command, "env", ft_strlen(sent->content.command)))
		ft_env(info->env_cpy);
	else if (!ft_strncmp(sent->content.command, "unset", ft_strlen(sent->content.command)))
		ft_unset(sent->content.args, info);
	else if (!ft_strncmp(sent->content.command, "cd", ft_strlen(sent->content.command)))
		ft_cd(sent->content.args);
	else if (!ft_strncmp(sent->content.command, "export", ft_strlen(sent->content.command)))
		ft_export(sent->content.args, info);
	else
		//exeqv;
		(void)sent;
}
