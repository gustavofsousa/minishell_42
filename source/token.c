/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 21:01:14 by gusousa           #+#    #+#             */
/*   Updated: 2023/02/09 17:27:51 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	categorize_elements(t_cell **list)
{
	t_cell	*list_keep;

	list_keep = (*list);
	while ((*list))
	{
		if (!ft_strncmp((*list)->content, "|", 1))
			(*list)->token = piper;
		else if (!ft_strncmp((*list)->content, ">", 1)
				|| !ft_strncmp((*list)->content, "<", 1))
			(*list)->token = redirect;
		else if (!ft_strncmp((*list)->content, ">>", 2)
				|| !ft_strncmp((*list)->content, "<<", 2))
			(*list)->token = redirect;
		else
			(*list)->token = word;
		*list = (*list)->next;
	}
	*list = list_keep;	
}
