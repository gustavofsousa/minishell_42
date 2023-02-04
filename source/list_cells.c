/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:09:14 by gusousa           #+#    #+#             */
/*   Updated: 2023/02/03 14:34:40 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	create_new_cell(t_cell **list_cells, char *str)
{
	t_cell	*new_cell;

	new_cell = new_cell(str);
	lst_add_back(list_cells, new_cell);

}

void	new_cell(char *str)
{
	t_cell	*cell;

	cell = malloc(sizeof(t_cell));
	if (!cell)
		return (NULL);
	cell->content = str;
	cell->id = id;
	cell->next = NULL;
}

void	list_add_back(t_cell **list, t_cell *new_cell)
{

	if (!(*list))
	{
		*list = new_cell;
		return ;
	}
	while (*list->next != NULL)
		*list = *list->next;
	list->next = new_node;
}

void	list_clear_cells(t_cell list)
{
	t_cell	*tmp;

	while (*list)
	{
		tmp = (*list)->next;
		free(*list);
		*list = aux;
	}
	*list = NULL;
}
