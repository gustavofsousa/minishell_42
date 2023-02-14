/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   golfer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:58:51 by gusousa           #+#    #+#             */
/*   Updated: 2023/02/14 15:16:05 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

void	golfer(t_sentence *sent)
{
	// Multipiping
	qtd_sent = count_sentence(sent);
	if (qtd_sent > 1)
		create_fork(sent);

	//Escolher comando
	if (ftstrncmp(sent->command, "pwd", ft_strlen(sent->command)))
		ft_pwd();
	else if (ftstrncmp(sent->command, "echo", ft_strlen(sent->command)))
		ft_echo(sent->args);
	else if (ftstrncmp(sent->command, "exit", ft_strlen(sent->command)))
		ft_exit(sent->args);
	else if (ftstrncmp(sent->command, "env", ft_strlen(sent->command)))
		ft_env(sent->args);
	else if (ftstrncmp(sent->command, "unset", ft_strlen(sent->command)))
		ft_unset(sent->args);
	else if (ftstrncmp(sent->command, "cd", ft_strlen(sent->command)))
		ft_cd(sent->args);
	else if (ftstrncmp(sent->command, "export", ft_strlen(sent->command)))
		ft_export(sent->args);
	else
		//arqv;
		(void)sent;
}
