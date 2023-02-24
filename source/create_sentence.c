/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_sentence.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 11:18:42 by gusousa           #+#    #+#             */
/*   Updated: 2023/02/24 21:32:34 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_sentence	*new_sent(char *str1, char *str2)
{
	t_sentence *sent;

	sent = malloc(sizeof(t_sentence));
	if (!sent)
		return (NULL);
	sent->command = ft_strdup(str1);
	sent->args = ft_strdup(str2);
	sent->next = NULL;
	return (sent);
}

void	sent_addback(t_sentence **list, t_sentence *new_sent)
{
	t_sentence	*list_keep;

	if (*list == NULL)
		*list = new_sent;
	else
	{
		list_keep = *list;
		while ((*list)->next != NULL)
			*list = (*list)->next;
		(*list)->next = new_sent;
		*list = list_keep;
	}
}

int	count_sentences(t_cell *list)
{
	int	len;

	len = 1;
	while (list)
	{
		if (list->token == piper)
			len++;
		list = list->next;
	}
	return (len);
}

/*
 * Criar a sentença para enviar para os comandos.
 */
// Fazer aqui o redirect.
// e Heredoc
t_sentence	*create_sentence(t_cell *list_in, t_info *info)
{
	int			first_round;
	t_sentence	*sent;

	info->qtd_sent = count_sentences(list_in);
	first_round = 1;
	while (list_in)
	{
		if (first_round == 1)
		{
//			sent_addback(list_in->content[0], list_in->content[1]);
			sent->command = ft_strdup(list_in->content);
			first_round = 0;
		}
		else if (list_in->token == piper)
			first_round = 1;
		else
		{
			sent->args == ft_strjoin(list_in->content);//colocar um if de se nao tiver nada, dar um dup.
		}
		list_in = list_in->next;
	}
	// clear_list_initial().
	return (sent);
}
