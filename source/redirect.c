/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 11:18:42 by gusousa           #+#    #+#             */
/*   Updated: 2023/03/03 14:50:11 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	errno;
void	do_heredoc(t_sentence *sent)
{
	(void)sent;
}

void	deal_error(t_sentence *sent, char redir)
{
	if (redir == '>')
	{
		if (sent->output == -1)
			//exit(0);
		//printf("%s/n", strerror(errno));
		perror("Error in redirect:");
	}
}

void	create_new_fd(t_sentence *sent, t_cell *list_in, char redir, char redir2)
{
	if (redir == '>')
	{
		if (redir2 == '>')
			sent->output = open(list_in->next->content,  O_CREAT, O_WRONLY,O_APPEND);
		else
			sent->output = open(list_in->next->content,  O_CREAT, O_WRONLY,O_TRUNC);
	}
	else
	{
		if (redir2 == '<')
			do_heredoc(sent);
		else//?
			sent->input = open(list_in->next->content, O_WRONLY, O_CREAT, O_TRUNC);
	}
}

void	close_old_fd(t_sentence *sent, char redir)
{
	if (redir == '>')
	{
		if (sent->output != 1)
			close(sent->output);
	}
	else
	{
		if (sent->input != 0)
			close(sent->input);
	}
}

/*
 * Tenho que fechar o fd anterior do output ou input(se nao for o padrao 0 e 1).
 * Cro um fd novo (com open), criando o arquivo.
 * A flag do open vai depende do tipo de seta.
 * E tratar error se o open falhar (retorno -1, e o errno diz qual foi)
 * Coloco o fd como output(> ou >>) ou input(<) daquela sentença.
 */
void	open_redirect(t_cell *list_in, t_sentence *sent)
{
	char	redir;
	char	redir2;

	redir = list_in->content[0];
	redir2 = list_in->content[1];
	close_old_fd(sent, redir);
	create_new_fd(sent, list_in,  redir, redir2);
	deal_error(sent, redir);
}
