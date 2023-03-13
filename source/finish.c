/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:27:56 by gusousa           #+#    #+#             */
/*   Updated: 2023/03/13 15:47:12 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	close_fdes(t_info *info)
{
	t_list_sent *sentence;

	sentence = info->head;
	while (sentence)
	{
		if (sentence->content.input != 0)
		{
			close(sentence->content.input);
			sentence->content.input = 0;
		}
		if (sentence->content.output != 1)
		{
			close(sentence->content.output);
			sentence->content.output = 1;
		}
		sentence = sentence->next;
	}
}

void	freeing_local(char *right_path, char **right_args)
{
	int		i;

	if (right_path)
		free(right_path);
	if (right_args)
	{
		i = -1;
		while (right_args[++i])
			free(right_args[i]);
		free(right_args);
	}
}

void	point_to_null(t_info *info, t_cell **list_cells, t_list_sent **sentence)
{
	info->prompt = NULL;
	info->qtd_sent = 0;
	info->last_pid = -1;
	info->head = NULL;
	info->nbr_pids= NULL;
	*list_cells = NULL;	
	*sentence = NULL;
	info->fd_heredoc = NULL;
	g_status = 0;
}

void	reset(t_info *info, t_cell **list_cells, t_list_sent *sentence)
{
	int	i;

	free(info->prompt);
	close_fdes(info);
	list_clear_cells(list_cells);
	ft_lstclear_sent(&sentence);
	free(info->nbr_pids);
	if (info->fd_heredoc)
	{
		i = -1;
		while (info->fd_heredoc[++i] != -1)
			close(info->fd_heredoc[i]);
		free(info->fd_heredoc);
	}
	point_to_null(info, list_cells, &sentence);
	//close fd's i opened in redirect.
}

void	finish_program(t_info *info, t_cell **list_cells, t_list_sent *sentence)
{
	int	i;

	reset(info, list_cells, sentence);
	i = -1;
	if (info->env_cpy)
	{
		while (info->env_cpy[++i])
			free(info->env_cpy[i]);
		free(info->env_cpy);
	}
	info->env_cpy = NULL;
	exit (0);
}

