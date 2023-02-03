/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 21:01:14 by gusousa           #+#    #+#             */
/*   Updated: 2023/02/03 21:13:53 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	categorize_elemnts(t_cell **list_cells)
{
	t_cell	*list_keep;

	list_keep = *list_cells;
	while (*list_cells)
	{
		if (ft_strncmp(*list_cells->content, "|", 1)
			*list_cells->token = pipe;
		else if (ft_strncmp(*list_cells->content, ">", 1)
			*list_cells->token = redirect;
		else if (ft_strncmp(*list_cells->content, "<", 1)
			*list_cells->token = redirect;
		else if (ft_strncmp(*list_cells->content, ">>", 2)
			*list_cells->token = redirect;
		else if (ft_strncmp(*list_cells->content, "<<", 2)
			*list_cells->token = redirect;
		else
			*list_cells->token = word;
		*list_cells = list_cells->next;
	}
	*list_cells = list_keep;	
}
