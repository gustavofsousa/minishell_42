/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 11:18:42 by gusousa           #+#    #+#             */
/*   Updated: 2023/03/04 17:55:04 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	errno;
void	do_heredoc(t_info *info)
{
	char	*cmd;
	int		i;
	int		*new_fd;
	int		fildes[2];
	int		sucess;

	sucess = pipe(fildes);
	i = 1;
	if (info->fd_heredoc)
	{
		while (info->fd_heredoc[i] != -10)
			i++;
	}
	new_fd = malloc (sizeof(int) * i);
	new_fd[i--] = -10;
	new_fd[i] = fildes[0];
	while (i--)
		new_fd[i] = info->fd_heredoc[i];
	free(info->fd_heredoc);
	info->fd_heredoc = new_fd;
	while (42)
	{
		cmd = readline(">");
		if (!ft_strncmp(cmd, list_in->next.content, ft_strlen(cmd)))
			break;
		ft_putendl_fd(cmd, fildes[1]);
		free(cmd);
	}
	close (fildes[1]);
}

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

void	create_new_fd(t_sentence *sent, t_cell *list_in, char redir, char redir2, t_info *info)
{
	if (redir == '>')
	{
		if (redir2 == '>')
			sent->output = open(list_in->next->content, O_WRONLY | O_CREAT | O_APPEND,
					0644);
		else
			sent->output = open(list_in->next->content,  O_CREAT | O_WRONLY | O_TRUNC,
					0644);
	}
	else
	{
		if (redir2 == '<')
			do_heredoc(info);
		else
			sent->input = open(list_in->next->content, O_RDONLY);
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
void	open_redirect(t_cell *list_in, t_sentence *sent, t_info *info)
{
	char	redir;
	char	redir2;

	redir = list_in->content[0];
	redir2 = list_in->content[1];
	if (list_in->next && list_in->next->token == word)
	{
		close_old_fd(sent, redir);
		create_new_fd(sent, list_in,  redir, redir2, info);
		deal_error(sent, redir);
	}
	else
		ft_putstr_fd("syntax error near unexpected token 'newline'", 2);
	}
