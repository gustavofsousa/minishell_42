/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:57:41 by gusousa           #+#    #+#             */
/*   Updated: 2023/03/03 17:27:47 by parnaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
 * Apaga onde estava o nome da variável e coloca o valor dela.
 */
void	substitute(t_cell **list, t_info info, int index)
{
	int len;

	len = 0;
	len = ft_strlen((*list)->content);
	free((*list)->content);
	(*list)->content = NULL;
	(*list)->content = ft_strdup(info.env_cpy[index]+len);
}

/*
 * Compara se depois do $ a variável está com nome igual.
 */
int	look_for_variable(t_cell *list, t_info info)
{	
	int	i;
	int len;

	//verificar se tem essa variavel na env, se sim retornar o index
	i = 0;
	len = 0;
	while (list != NULL)
	{
		i = 0;
		while (info.env_cpy[i])
		{
			len = ft_strlen(list->content);
			if(!ft_strncmp(list->content+1, info.env_cpy[i], len-1))
			{
				return (i);
			}
			 i++;
		}
		list = list->next;
	}
	return (0);
}

int	check_quotes(t_cell **list)
{
	int	i;
	char str;

	i = 0;
	str = list->content;

	
}

void	expand_variable(t_cell **list_cell, t_info info)
{
	t_cell	*list_move;
	int		index;

	index = 0;
	list_move = *list_cell;
	while (list_move != NULL)
	{
		//check quotes
		printf("%s\n", list_move->content);
		if (ft_strchr(list_move->content, '$'))
		{
			index = look_for_variable(list_move, info);
			if (index)
			{
				substitute(&list_move, info, index);
			}
		}
		list_move = list_move->next;
	}
}
