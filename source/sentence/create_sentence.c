/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_sentence.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 11:18:42 by gusousa           #+#    #+#             */
/*   Updated: 2023/03/09 13:34:47 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

enum e_command	set_command(char *command)
{
	int	len;

	len = ft_strlen(command);
	if (!ft_strncmp(command, "pwd", len))
		return (pwd);
	else if (!ft_strncmp(command, "echo", len))
		return (echo);
	else if (!ft_strncmp(command, "exit", len))
		return (exiter);
	else if (!ft_strncmp(command, "env", len))
		return (env);
	else if (!ft_strncmp(command, "unset", len))
		return (unset);
	else if (!ft_strncmp(command, "cd", len))
		return (cd);
	else if (!ft_strncmp(command, "export", len))
		return (exporter);
	return (no_builtin);
}

t_cell	*new_sent(t_cell *list_in, t_list_sent **list_sentence, t_info *info)
{
	int			n_round;
	t_sentence	sent_node;

	n_round = 0;
	sent_node.input = 0;
	sent_node.output = 1;
	sent_node.args = NULL;
	while (list_in && list_in->token != piper)
	{
		if (list_in->token == redirect)
		{
			open_redirect(list_in, &sent_node, info);
			list_in = list_in->next;
			if (list_in == NULL)
				break ;
		}
		else if (n_round == 0)
			sent_node.command = set_command(list_in->content);
		else if (n_round == 1)
			sent_node.args = ft_strdup(list_in->content);
		else
		{
			if (list_in->space == 1)
				sent_node.args = ft_strjoin_free(sent_node.args, " ");
			sent_node.args = ft_strjoin_free(sent_node.args, list_in->content);
		}
		n_round++;
		if (n_round == 1 && sent_node.command == no_builtin)
		{
			sent_node.args = ft_strdup(list_in->content);
			n_round++;
		}
		list_in = list_in->next;
		if (list_in == NULL)
			break ;
	}
	ft_lstadd_back_sent(list_sentence, ft_lstnew_sent(sent_node));
	return (list_in);
}

/*
 * Criar a sentença para enviar para os comandos.
 */
// Fazer aqui o redirect.
// e Heredoc
t_list_sent	*create_sentence(t_cell *list_in, t_info *info)
{
	int			i;
	t_list_sent	*sent;

	sent = NULL;
	info->qtd_sent = count_sentences(list_in);
	i = 0;
	while (i < info->qtd_sent)
	{
		list_in = new_sent(list_in, &sent, info);
		if (list_in == NULL)
			break ;
		i++;
		list_in = list_in->next;
	}
	return (sent);
}
