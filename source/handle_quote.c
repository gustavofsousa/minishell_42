/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 19:16:19 by gusousa           #+#    #+#             */
/*   Updated: 2023/02/09 19:32:33 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_quote(t_cells **list_cells)
{
	t_cells	*list_keep;
	int		quote;
	char	*keep_str;

	list_keep = *list_cells;
	quote = 0;
	while (*list_cells)
	{
		// Encontro da " primeira vez
		if (ft_strchr(*list_cells->content, '"') && quote == 0)
		{
			quote = 1;
			cell_begin_word = *list_cells;
		}
		// Encontro da " segunda vez.
		else if (ft_strchr(*list_cells->content, '"') && quote == 1)
		{
			str_keep = cell_begin_word->content;
			cell_begin_word->content = ft_strjoin(cell_begin_word->content, list_cells->content);
			free(str_keep);
		}
		// Palavras entre inicio e fim de ".
		else if (quote == 1)
		{
			str_keep = cell_begin_word->content;
			cell_begin_word->content = ft_strjoin(cell_begin_word->content, " ");
			free(str_keep);
			str_keep = cell_begin_word->content;
			cell_begin_word->content = ft_strjoin(cell_begin_word->content, list_cells->content);
			free(str_keep);
		}
		*list_cells = *list_cells->next;
	}
	*list_cells = list_keep;
}
