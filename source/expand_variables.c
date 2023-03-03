/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:57:41 by gusousa           #+#    #+#             */
/*   Updated: 2023/03/02 17:24:50 by parnaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
 * Apaga onde estava o nome da variável e coloca o valor dela.
 */
void	substitute(t_cell **list)
{
	t_cell *temp;
	
	temp = (*list);
	while (temp != NULL)
	{
		printf("%s\n", temp->content);
		temp = temp->next;
	}
}

/*
 * Compara se depois do $ a variável está com nome igual.
 */
int	look_for_variable(t_cell *list, t_info info)
{
	(void)list;
	(void)info;

	//verificar se tem essa variavel na env, se sim retornar o index
	return (1);
}

void	expand_variable(t_cell **list_cell, t_info info)
{
	t_cell	*list_move;

	list_move = *list_cell;
	(void) info;
	while (list_move != NULL)
	{

		printf("%s\n", list_move->content);
		list_move = list_move->next;
		/*if (ft_strchr(list_move->content, '$'))
		{
			if (look_for_variable(list_move, info))
			{
				substitute(&list_move);
			}
		}
		list_move = list_move->next;
		*/
	}
}
