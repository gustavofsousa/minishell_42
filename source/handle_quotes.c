/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 19:16:19 by gusousa           #+#    #+#             */
/*   Updated: 2023/02/14 13:25:57 by gusousa          ###   ########.fr       */
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
	/*
	char	*to_join;
	int		begin;
	int		end;
	int		first;
	*/
	int		i;
	int		c;
	int		m;

	printf("estou aqui");
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
	printf("%s\n", (*init_cell)->content);
	printf("aqui");





	/*
	free((*init_cell)->content);
	(*init_cell)->content = NULL;
	first = 1;
	i = 0;
	end = 0;
	begin = 0;
	while (str[i - 1])
	{
		if (str[i] != '"')
			end++;
		else if (str[i] == '"' || str[i] == '\0')
		{
			to_join = ft_substr(str, begin, end);
			if (first == 1)
			{
				(*init_cell)->content = ft_strdup(to_join);
				first = 0;
			}
			else 
				ft_strjoin((*init_cell)->content, to_join);
			free(to_join);
			begin = end + 1;
			end = 0;
		}
		i++;
	}
	*/
	/*
	while (str[i])
	{
		// Se for a primeira vez para copiar.
		if ((*init_cell)->content == NULL && str[i] != '"')
			(*init_cell)->content = ft_strdup(&str[i]);
		// Copiar as outras vezes
		else if (str[i] != '"')
			ft_strjoin((*init_cell)->content, &str[i]);
		i++;
	}
	free(str);
	*/
}

void	join_cells(t_cell **init_cell, t_cell *list)
{
	if (list->space == 1)
		(*init_cell)->content = ft_strjoin_free((*init_cell)->content, " ");
	(*init_cell)->content = ft_strjoin_free((*init_cell)->content, list->content);
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
			deceive_quotes(init_cell);
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
