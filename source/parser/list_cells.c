/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_cells.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:09:14 by gusousa           #+#    #+#             */
/*   Updated: 2023/03/09 14:10:43 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	list_clear_cells(t_cell **list)
{
	t_cell	*tmp;

	while (*list)
	{
		tmp = (*list)->next;
		free(*list);
		*list = NULL;
		*list = tmp;
	}
	*list = NULL;
}

t_cell	*new_cell(char *str)
{
	t_cell	*cell;

	cell = malloc(sizeof(t_cell));
	if (!cell)
		return (NULL);
	cell->content = ft_strdup(str);
	cell->next = NULL;
	cell->space = 1;
	return (cell);
}

void	list_add_back(t_cell **list, t_cell *new_cell)
{
	t_cell	*list_keep;

	if (*list == NULL)
		*list = new_cell;
	else
	{
		list_keep = *list;
		while ((*list)->next != NULL)
			*list = (*list)->next;
		(*list)->next = new_cell;
		*list = list_keep;
	}
}

void	create_new_cell(t_cell **list_cells, char *str, int spce)
{
	t_cell	*nc;

	nc = new_cell(str);
	if (spce == 0)
		nc->space = 0;
	list_add_back(list_cells, nc);
}

void	delete_cell(t_cell **init_cell, t_cell **list)
{
	(*init_cell)->next = (*list)->next;
	free((*list)->content);
	free(*list);
	*list = NULL;
}
