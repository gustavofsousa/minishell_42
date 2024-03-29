/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 19:09:37 by gusousa           #+#    #+#             */
/*   Updated: 2023/03/24 12:05:46 by gusousa          ###   ########.fr       */
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
	sent->input = fildes[0];
	return (fildes[1]);
}

int	do_heredoc(t_cell *list_in, t_sentence *sent, t_info *info)
{
	char	*cmd;
	int		fd_write;

	cmd = NULL;
	fd_write = open_pipe_redir(sent);
	if (fd_write != -1)
	{
		g_status = 0;
		while (42)
		{
			cmd = readline(">");
			if (cmd == NULL || g_status != 0
				|| !ft_strncmp(cmd, list_in->next->content,
					ft_strlen(list_in->next->content) + 1))
				break ;
			ft_putendl_fd(cmd, fd_write);
			free(cmd);
			cmd = NULL;
		}
		if (g_status == 130)
			info->stop = 1;
		return (free(cmd), close(fd_write), 0);
	}
	return (0);
}
