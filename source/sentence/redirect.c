/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 11:18:42 by gusousa           #+#    #+#             */
/*   Updated: 2023/03/14 14:40:11 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	deal_error(t_sentence *sent, char redir)
{
	if (redir == '>')
	{
		if (sent->output == -1)
		{
			perror("Error in redirect");
			//finish_program();
		}
	}
	else if (redir == '<')
	{
		if (sent->input == -1)
		{
			perror("Error in redirect");
			//finish_program();
		}
	}
}

void	create_new_fd(t_sentence *sent, t_cell *list, char redir)
{
	char	redir2;

	redir2 = list->content[1];
	if (redir == '>')
	{
		if (redir2 == '>')
			sent->output = open(list->next->content,
					O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			sent->output = open(list->next->content,
					O_CREAT | O_WRONLY | O_TRUNC, 0644);
	}
	else
	{
		if (redir2 == '<')
			do_heredoc(list, sent);
		else
			sent->input = open(list->next->content, O_RDONLY);
	}
}

void	close_old_fd(t_sentence *sent, char redir)
{
	if (redir == '>')
	{
		if (sent->output != 1)
			close(sent->output);
	}
	else if (redir == '<')
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
int	open_redirect(t_cell *list_in, t_sentence *sent)
{
	char	redir;

	if (list_in->token == redirect)
	{
		redir = list_in->content[0];
		if (list_in->next && list_in->next->token == word)
		{
			close_old_fd(sent, redir);
			create_new_fd(sent, list_in, redir);
			//deal_error(sent, redir);
		}
		else
			ft_putstr_fd("syntax error near unexpected token 'newline'", 2);
		return (1);
	}
	return (0);
}
