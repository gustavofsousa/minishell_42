/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 19:16:19 by gusousa           #+#    #+#             */
/*   Updated: 2023/02/13 13:21:00 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	delete_cell(t_cell **c_b_w, t_cell **list)
{
	(*c_b_w)->next = (*list)->next;
	free((*list)->content);
	free(*list);
	// Tem que ver se a list está perdendo a referencia para próxima rodada.
}

/* Tratativa de aspas.
 * Quando achar uma aspas, copia os conteúdos dos próximos nós
 * até encontrar a última aspas.
 */
void	handle_quotes(t_cell **list)
{
	t_cell	*list_keep;
	t_cell	*c_w_b;//cell_begin_word.
	int		quote;
	char	*str_keep;

	list_keep = *list;
	c_w_b = *list;
	quote = 0;
	while (*list)
	{
		// Encontro da " primeira vez
		if (ft_strchr((*list)->content, '"') && quote == 0)
		{
			quote = 1;
			c_w_b = *list;
		}
		// Encontro da " segunda vez.
		else if (ft_strchr((*list)->content, '"') && quote == 1)
		{
			str_keep = ft_strdup(c_w_b->content);
			c_w_b->content = ft_strjoin(c_w_b->content, (*list)->content);
			free(str_keep);
			delete_cell(&c_w_b, list);
		}
		// Palavras entre inicio e fim de ".
		else if (quote == 1)
		{
			str_keep = ft_strdup(c_w_b->content);
			c_w_b->content = ft_strjoin(c_w_b->content, (*list)->content);
			free(str_keep);
			delete_cell(&c_w_b, list);
		}
		*list = (c_w_b)->next;
	}
	*list = list_keep;
}
