/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 19:16:19 by gusousa           #+#    #+#             */
/*   Updated: 2023/02/10 09:53:13 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	delete_cell(t_cell **c_b_w, t_cell **list_cells)
{
	(*c_b_w)->next = (*list_cells)->next;
	free((*list_cells)->content);
	free(list_cells);
	// Tem que ver se a list_cells está perdendo a referencia para próxima rodada.
}

void	handle_quotes(t_cell **list_cells)
{
	t_cell	*list_keep;
	t_cell	*cell_begin_word;
	int		quote;
	char	*str_keep;

	list_keep = *list_cells;
	quote = 0;
	while (*list_cells)
	{
		// Encontro da " primeira vez
		if (ft_strchr((*list_cells)->content, '"') && quote == 0)
		{
			quote = 1;
			cell_begin_word = *list_cells;
		}
		// Encontro da " segunda vez.
		else if (ft_strchr((*list_cells)->content, '"') && quote == 1)
		{
			str_keep = cell_begin_word->content;
			cell_begin_word->content = ft_strjoin(cell_begin_word->content, (*list_cells)->content);
			free(str_keep);
			delete_cell(&cell_begin_word, list_cells);
		}
		// Palavras entre inicio e fim de ".
		else if (quote == 1)
		{
			str_keep = cell_begin_word->content;
			cell_begin_word->content = ft_strjoin(cell_begin_word->content, " ");
			free(str_keep);
			str_keep = cell_begin_word->content;
			cell_begin_word->content = ft_strjoin(cell_begin_word->content, (*list_cells)->content);
			free(str_keep);
			delete_cell(&cell_begin_word, list_cells);
		}
		*list_cells = (cell_begin_word)->next;
	}
	*list_cells = list_keep;
}
