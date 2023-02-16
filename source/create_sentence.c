/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_sentence.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 11:18:42 by gusousa           #+#    #+#             */
/*   Updated: 2023/02/16 11:28:57 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

/*
 * Criar a sentença para enviar para os comandos.
 */
// Fazer aqui o redirect.
t_sentence	*create_sentence(t_cell *list_cells, t_info *info)
{
	int	i;
	t_sentence	*sent;

	info->qtd_sent = count_cells(list_cells);
	i = 0;
	while (i < info->qtd_sent)
	{
		// Malloca o nó completo
		// Dá um strdup para o commando
		// Dá um dup/join para os outros argumentos.
	}
	return (sent);
}
