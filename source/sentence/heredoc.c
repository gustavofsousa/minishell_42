/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 19:09:37 by gusousa           #+#    #+#             */
/*   Updated: 2023/03/13 19:49:08 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	open_pipe_redir(t_sentence *sent)
{
	int		fildes[2];
	int		success;

	success = pipe(fildes);
	if (success == -1)
		return (-1);
	if (sent->input != 0)
		close(sent->input);
	sent->input = fildes[0];
	return (fildes[1]);
}

void	do_heredoc(t_cell *list_in, t_sentence *sent)
{
	char	*cmd;
	int		fd_write;

	fd_write = open_pipe_redir(sent);
	if (fd_write != -1)
	{
		g_status = 0;
		while (42)
		{
			cmd = readline(">");
			// Ou cmd == null
			// se o g_global 'e 1.
			if (!ft_strncmp(cmd, list_in->next->content, ft_strlen(cmd))
				|| g_status == 1
				|| cmd == NULL)
				break ;
			ft_putendl_fd(cmd, fd_write);
			free(cmd);
			cmd = NULL;
		}
		free(cmd);
		close(fd_write);
	}
}
