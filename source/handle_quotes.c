/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 19:16:19 by gusousa           #+#    #+#             */
/*   Updated: 2023/02/14 19:08:03 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	delete_cell(t_cell **init_cell, t_cell **list)
{
	(*init_cell)->next = (*list)->next;
	free((*list)->content);
	free(*list);
	*list = NULL;
}

void	deceive_quotes(t_cell **init_cell)
{
	char	*str;
	int		i;
	int		c;
	int		m;

	str = ft_strdup((*init_cell)->content);
	i = 0;
	m = 0;
	while (str[i])
	{
		if (str[i] == 34)//aspas duplas
		{
			str[i] = 7;
			c = i;
			while (str[c] != '\0')
			{
				(*init_cell)->content[c - m] = str[c + 1];
				c++;
			}
			m++;
		}
		i++;
	}
	(*init_cell)->content[i] = '\0';
	free(str);
}

int	cpy_in_quotes(t_cell **init_cell, char *content, int *i)
{
	int	fq;
	char	quote;

	quote = content[*i];
	fq = 1;
	while (content[*i] != '\0' && fq == 1)
	{
		ft_strjoin_char((*init_cell)->content, content[*i]);
		if (content[*i] == quote)
			fq = 0;
		(*i)++;
	}
	return (fq);
}

// Precisa ver se ele está fazendo a cópia antes de chegar em uma aspas.
void	join_cells(t_cell **init_cell, t_cell *list)
{
	int	i;
	int	fq;

	fq = 0;
	i = 0;
	while (list->content[i])
	{
		if (list->content[i] == '"' || list->content[i] == '\'')
			fq = cpy_in_quotes(init_cell, list->content, &i);
		if (fq != 0)
			printf("Error not closing quotes\n");//lidar com erro aqui
		i++;
	}

//	if (list->space == 1)
//		(*init_cell)->content = ft_strjoin_free((*init_cell)->content, " ");
//	(*init_cell)->content = ft_strjoin_free((*init_cell)->content, list->content);
}

/*
 * Quando achar uma aspas, copia os conteúdos dos próximos nós
 * até encontrar a última aspas.
 */
void	search_for_quotes(t_cell **list, t_cell **init_cell, int quote)
{
	// Encontro da " primeira vez.
	if (ft_strchr((*list)->content, '"') && quote == 0)
	{
		quote = 1;
		*init_cell = *list;
	}
	// Palavras entre inicio e fim de ".
	if (quote == 1)
	{
		join_cells(init_cell, *list);
		// Final das aspas.
		if (ft_strchr((*list)->content, '"'))
		{
			quote = 0;
			//deceive_quotes(init_cell);
		}
		delete_cell(init_cell, list);
	}

}

/*
 * Tratativa de aspas.
 * Objetivo é juntar em uma única célula tudo que tiver entre aspas.
 */
void	handle_quotes(t_cell **list_cells)
{
	t_cell	*list_move;
	t_cell	*init_cell;//cell_begin_word.
	int		quote;

	quote = 0;
	list_move = *list_cells;
	init_cell = *list_cells;
	while (list_move != NULL)
	{
		search_for_quotes(&list_move, &init_cell, quote);
		printf("OUT\n");
		list_move = (init_cell)->next;
	}
}
