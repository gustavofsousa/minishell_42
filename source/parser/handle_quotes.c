/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 19:16:19 by gusousa           #+#    #+#             */
/*   Updated: 2023/03/04 12:07:04 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	delete_cell(t_cell **init_cell, t_cell **list)
{
	(*init_cell)->next = (*list)->next;
	free((*list)->content);
	free(*list);
	*list = NULL;
}

void	join_cells(t_cell **init_cell, char *content, int *fq, char *quote)
{
	int	i;

	i = 0;
	while (content[i])
	{
		// Achando 1ª aspas.
		if (*fq == 1 && content[i] == *quote)
			*fq = 2;
		// Fechando as aspas.
		else if (*fq == 2 && content[i] == *quote)
			*fq = 0;
		// Achando outro início de aspas.
		else if (*fq == 0 && (content[i] == '"' || content[i] == '\''))
		{
				*fq = 1;//Com novas aspas.
				*quote = content[i];
		}
		else if ((*init_cell)->content == NULL)
		{
				(*init_cell)->content = malloc(2);
				(*init_cell)->content[0] = content[i];
				(*init_cell)->content[1] = '\0';
		}
		// Copiando.
		else
			(*init_cell)->content = ft_strjoin_char((*init_cell)->content,
				content[i]);
		i++;
	}
	free(content);
}

char	which_quotes(char *str)
{
	while (*str)
	{
		if (*str == '"')
			return (*str);
		if (*str == '\'')
			return (*str);
		str++;
	}
	return (0);
}

/*
 * Quando achar uma aspas, copia os conteúdos dos próximos nós
 * até encontrar a última aspas.
 */
void	search_quotes(t_cell **init_cell, t_cell **list, int *fq, char *quote)
{
	char	*first_word;

	// Defino o início da minha célula, 1ª aspas.
	if (*fq == 0
		&& (ft_strchr((*list)->content, '"')
			|| ft_strchr((*list)->content, '\'')))
	{
		*fq = 1;
		*quote = which_quotes((*list)->content);
		*init_cell = *list;
		first_word = ft_strdup((*list)->content);
		free((*init_cell)->content);
		(*init_cell)->content = NULL;
		join_cells(init_cell, first_word, fq, quote);
		if ((*list)->space == 1)
			(*init_cell)->content = ft_strjoin_char((*init_cell)->content, ' ');
	}
	// Copiando as palavras quando acha as aspas, inicio meio e fim.
	else if (*fq > 0)
	{
		join_cells(init_cell, ft_strdup((*list)->content), fq, quote);
		if ((*list)->space == 1)
			(*init_cell)->content = ft_strjoin_char((*init_cell)->content, ' ');
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
	t_cell	*init_cell;
	int		fq;
	char	quote;

	fq = 0;
	quote = '0';
	list_move = *list_cells;
	init_cell = *list_cells;
	while (list_move != NULL)
	{
		search_quotes(&init_cell, &list_move, &fq, &quote);
		if (list_move == NULL)
			list_move = init_cell->next;
		else
			list_move = list_move->next;
	}
	if (fq > 0)
		printf("Error, aspas não fechou");
}
