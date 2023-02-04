/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_cells.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:09:14 by gusousa           #+#    #+#             */
/*   Updated: 2023/02/04 11:07:09 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_cell	*new_cell(char *str)
{
	t_cell	*cell;

	cell = malloc(sizeof(t_cell));
	if (!cell)
		return (NULL);
	cell->content = str;
	cell->next = NULL;
	return (cell);
}

void	list_add_back(t_cell **list, t_cell *new_cell)
{
	if (*list == NULL)
	{
		*list = new_cell;
		printf("Create cell->\t%s\n", new_cell->content);
		return ;
	}
	while ((*list)->next != NULL)
		*list = (*list)->next;
	(*list)->next = new_cell;
	printf("Create cell->\t%s\n", new_cell->content);
}

void	create_new_cell(t_cell **list_cells, char *str)
{
	list_add_back(list_cells, new_cell(str));
}

void	list_clear_cells(t_cell **list)
{
	t_cell	*tmp;

	while (*list)
	{
		tmp = (*list)->next;
		free(*list);
		*list = tmp;
	}
	*list = NULL;
}
