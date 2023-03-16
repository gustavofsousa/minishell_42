/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_space.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 14:11:12 by gusousa           #+#    #+#             */
/*   Updated: 2023/03/16 18:31:33 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	add_more_spaces(t_list_sent **sent, int qtd_spaces)
{
	if (qtd_spaces > 1)
	{
		(void)sent;
	}
}

int	count_elements(char *str)
{
	int	i;
	int	qtd_word;

	if (str == NULL)
		return (-1);
	qtd_word = 1;
	i = 0;
	while (str[i + 1])
	{
		if (str[i] != ' ' && str[i + 1] == ' ')
			qtd_word++;
		i++;
	}
	return (qtd_word);
}

/*
*	A funçao conta os elementos (para saber qual parte do args é)
Contar os espaços (para dar o join com espaçoes)
Quando acha um pipe (fora de aspas), altera para próxima sentença.
*/
void	handle_space(t_list_sent **sent, t_info info)
{
	int	qtd_elem;
	int	qtd_spaces;
	int	fq;

	fq = 0;
	qtd_spaces = 0;
	qtd_elem = count_elements(info.prompt);
	while (info.prompt[i])
	{
		if ((info.prompt[i] == '"' || info.prompt[i] == "\'")
			&& fq == 0)
		{
			fq = 1;
			quote = which_quote(info.prompt[i]);
		}
		else if (fq == 1 && info.prompt[i] == quote)
			fq = 0;
		if (fq == 1 && info.prompt[i] == ' ')
		{
			qtd_spaces++;
		}
		else if (fq == 1 && info.prompt[i] != ' ')
		{
			add_more_space(sent, qtd_spaces);
			qtd_spaces = 0;
		}
		i++;
	}

}
