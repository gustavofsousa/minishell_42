/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:57:41 by gusousa           #+#    #+#             */
/*   Updated: 2023/02/15 10:58:16 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
 * Apaga onde estava o nome da variável e coloca o valor dela.
 */
void	substitute(t_cell **list)
{
	(void)list;
}

/*
 * Compara se depois do $ a variável está com nome igual.
 */
int	look_for_variable(t_cell *list, t_info info)
{
	(void)list;
	(void)info;
	return (1);
}

void	expand_variable(t_cell **list_cell, t_info info)
{
	t_cell	*list_move;

	list_move = *list_cell;
	while (list_move != NULL)
	{
		if (ft_strchr(list_move->content, '$'))
		{
			if (look_for_variable(list_move, info))
			{
				substitute(&list_move);
			}
		}
		list_move = list_move->next;
	}
}
