/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 19:16:19 by gusousa           #+#    #+#             */
/*   Updated: 2023/02/14 12:10:13 by gusousa          ###   ########.fr       */
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
	str = ft_strdup((*c_w_b)->content);
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
				(*c_w_b)->content[c - m] = str[c + 1];
				c++;
			}
			m++;
		}
		i++;
	}
	(*c_w_b)->content[i] = '\0';
	free(str);
	printf("%s\n", (*c_w_b)->content);
	printf("aqui");





	/*
	free((*c_w_b)->content);
	(*c_w_b)->content = NULL;
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
				(*c_w_b)->content = ft_strdup(to_join);
				first = 0;
			}
			else 
				ft_strjoin((*c_w_b)->content, to_join);
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
		if ((*c_w_b)->content == NULL && str[i] != '"')
			(*c_w_b)->content = ft_strdup(&str[i]);
		// Copiar as outras vezes
		else if (str[i] != '"')
			ft_strjoin((*c_w_b)->content, &str[i]);
		i++;
	}
	free(str);
	*/
}

void	join_cells(t_cell **c_w_b, t_cell *list)
{
	if (list->space == 1)
		(*c_w_b)->content = ft_strjoin_free((*c_w_b)->content, " ");
	(*c_w_b)->content = ft_strjoin_free((*c_w_b)->content, list->content);
}

void	search_for_quotes(t_cell **list, t_cell **c_w_b)
{
	int		quote;

	quote = 0;
	// Encontro da " primeira vez
	if (ft_strchr((*list)->content, '"') && quote == 0)
	{
		quote = 1;
		*c_w_b = *list;
	}
	// Palavras entre inicio e fim de ".
	else if (quote == 1)
	{
		join_cells(c_w_b, *list);
		if (ft_strchr((*list)->content, '"'))
		{
			quote = 0;
			printf("echo");
			deceive_quotes(c_w_b);
		}
		delete_cell(c_w_b, list);
	}

}

/* Tratativa de aspas.
 * Objetivo é juntar em uma única célula tudo que tiver entre aspas.
 *
 * Quando achar uma aspas, copia os conteúdos dos próximos nós
 * até encontrar a última aspas.
 */
void	handle_quotes(t_cell **list_cells)
{
	t_cell	*list_move;
	t_cell	*c_w_b;//cell_begin_word.

	list_move = *list_cells;
	c_w_b = *list_cells;
	while (list_move)
	{
		search_for_quotes(&list_move, &c_w_b);
		list_move = (c_w_b)->next;
	}
}

// E quando tiver as duas "" no mesmo nó. "assim".
