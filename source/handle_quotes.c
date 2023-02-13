/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 19:16:19 by gusousa           #+#    #+#             */
/*   Updated: 2023/02/13 17:03:16 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	delete_cell(t_cell **c_b_w, t_cell **list)
{
	(*c_b_w)->next = (*list)->next;
	free((*list)->content);
	free(*list);
	*list = NULL;
	// Tem que ver se a list está perdendo a referencia para próxima rodada.
}

void	deceive_quotes(t_cell **c_w_b)
{
	char	*str;
	int		i;
	
	str = ft_strdup((*c_w_b)->content);
	free((*c_w_b)->content);
	(*c_w_b)->content = NULL;
	i = 0;
	while (str[i])
	{
		if ((*c_w_b)->content == NULL && str[i] != '"')
			(*c_w_b)->content = ft_strdup(&str[i]);
		else if (str[i] != '"')
			ft_strjoin((*c_w_b)->content, &str[i]);
		i++;
	}
	free(str);
}

void	join_cells(t_cell **c_w_b, t_cell *list)
{
	char	*str_keep;
	
	if (list->space == 1)
	{
		str_keep = ft_strdup(" ");
		(*c_w_b)->content = ft_strjoin((*c_w_b)->content, str_keep);
		free(str_keep);
	}
	(*c_w_b)->content = ft_strjoin((*c_w_b)->content, list->content);
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
		// Palavras entre inicio e fim de ".
		else if (quote == 1)
		{
			join_cells(&c_w_b, *list);
			if (ft_strchr((*list)->content, '"'))
			{
				quote = 0;
				deceive_quotes(&c_w_b);
			}
			delete_cell(&c_w_b, list);
		}
		*list = (c_w_b)->next;
	}
	*list = list_keep;
}

// E quando tiver as duas "" no mesmo nó. "assim".
