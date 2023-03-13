/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 19:09:37 by gusousa           #+#    #+#             */
/*   Updated: 2023/03/13 19:10:58 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	open_pipe_redir(t_info *info)
{
	int		i;
	int		*new_fd;
	int		fildes[2];
	int		success;

	success = pipe(fildes);
	if (success == -1)
		return (-1);
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
	return (fildes[1]);
}

void	do_heredoc(t_cell *list_in, t_info *info)
{
	char	*cmd;
	int		fd_write;

	fd_write = open_pipe_redir(info);
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
