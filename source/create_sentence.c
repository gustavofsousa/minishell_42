/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_sentence.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 11:18:42 by gusousa           #+#    #+#             */
/*   Updated: 2023/02/15 12:13:40 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.c"

int	count_cells(t_cell *list)
{
	int	len;

	len = 0;
	while (list)
	{
		len++;
		list = list->next;
	}
	return (len);
}

// Fazer aqui o redirect.
t_sentence	*create_sentence(t_cell *list_cells, t_info *info)
{
	int	i;
	t_sentence	*sent;

	info->qtd_sent = count_cells(list_cells);
	i = 0;
	while (i < info->qtd_sent)
	{
		sent = malloc(sizeof(t_sentence));
		sent->commands = ft_strdup(list_cells->content[0]);
		while (list_cells->content[w++])
			sent->args = ft_strdup(list_cells->&content[1]);
	}
}
