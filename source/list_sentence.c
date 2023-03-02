/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_sentence.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 16:07:01 by gusousa           #+#    #+#             */
/*   Updated: 2023/03/02 20:37:50 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_lstclear_sent(t_list_sent **lst)
{
	t_list_sent	*aux;

	while (*lst)
	{
		aux = (*lst)->next;
		free(*lst);
		*lst = aux;
	}
	*lst = NULL;
}

void	ft_lstadd_back_sent(t_list_sent **lst, t_list_sent *new_node)
{
	if (*lst == NULL)
		*lst = new_node;
	else
	{
		// Talvez precise por um list_move.
		while ((*lst)->next != NULL)
			*lst = (*lst)->next;
		(*lst)->next = new_node;
	}
}

t_list_sent	*ft_lstnew_sent(t_sentence content)
{
	t_list_sent	*node;

	node = malloc(sizeof(t_list_sent));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}
