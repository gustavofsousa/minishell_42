/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 19:16:19 by gusousa           #+#    #+#             */
/*   Updated: 2023/03/27 17:44:25 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_strdup_char(char c)
{
	char	*str;

	str = malloc(2);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

void	join_cells(t_cell **init_cell, char *content, int *fq, char *quote)
{
	int	i;

	i = 0;
	while (content[i])
	{
		if (*fq == 1 && content[i] == *quote)
			*fq = 2;
		else if (*fq == 2 && content[i] == *quote)
			*fq = 0;
		else if (*fq == 0 && (content[i] == '"' || content[i] == '\''))
		{
				*fq = 1;
				*quote = content[i];
		}
		else if ((*init_cell)->content == NULL)
			(*init_cell)->content = ft_strdup_char(content[i]);
		else
			(*init_cell)->content = ft_strjoin_char((*init_cell)->content,
					content[i]);
		i++;
	}
	free(content);
}

static char	which_quotes(char *str)
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

void	search_quotes(t_cell **init_cell, t_cell **list, int *fq, char *quote)
{
	char	*first_word;

	if (*fq == 0 && (ft_strchr((*list)->content, '"')
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
	else if (*fq > 0)
	{
		join_cells(init_cell, ft_strdup((*list)->content), fq, quote);
		if ((*list)->space == 1)
			(*init_cell)->content = ft_strjoin_char((*init_cell)->content, ' ');
		delete_cell(init_cell, list);
	}
}

int	handle_quotes(t_cell **list_cells)
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
	return (1);
}
