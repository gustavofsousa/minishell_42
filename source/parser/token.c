/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 21:01:14 by gusousa           #+#    #+#             */
/*   Updated: 2023/03/27 18:37:45 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	call_error(t_cell **list, t_cell *list_keep)
{
	if (list_keep && list_keep->token == piper)
	{
		ft_putendl_fd("error: missing operand", 2);
		return (-1);
	}
	if (*list)
	{
		if ((*list)->next == NULL && (*list)->token == piper)
		{
			ft_putendl_fd("error: missing operand", 2);
			return (-1);
		}
	}
	return (0);
}

int	categorize_elements(t_cell **list)
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
		if (call_error(list, list_keep) == -1)
			return (-1);
		*list = (*list)->next;
	}
	if (call_error(list, list_keep) == -1)
		return (-1);
	*list = list_keep;
	return (1);
}
