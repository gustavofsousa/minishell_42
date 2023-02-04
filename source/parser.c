/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 13:40:15 by gusousa           #+#    #+#             */
/*   Updated: 2023/02/04 10:47:02 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*check_if_double(char *str, int *i)
{
	if (*(str + 1) == *str && *(str + 1) != '|')
	{
		(*i)++;
		return (ft_substr(str, 0, 2));
	}
	else
		return (ft_substr(str, 0, 1));
}

/*
 * As três opções para metadado é:
 * 1. Início da palavra
 * 2. Entre duas palavras. 
 * 3. Final da palavra.
 */
void	split_and_create(t_cell **list_cells, char *str)
{
	char	*new_word;
	int		i;

	while (*str)
	{
		i = 0;
		if (*str == '|' || *str == '>' || *str == '<')
		{
			new_word = check_if_double(str, &i);
			create_new_cell(list_cells, new_word);
			free(new_word);
			i++;
		}
		else
		{
			while (str[i] != '|' && str[i] != '>'
				&& str[i] != '<' && str[i] != '\0')
				i++;
			new_word = ft_substr(str, 0, i);
			create_new_cell(list_cells, new_word);
			free(new_word);
		}
		str += i;
	}
}

/*
 * Função para dividir as palavras do prompt em nós de uma lista.
 *
 * Andando em cada palavra, vendo se tem caracter
 * Se tiver, vê se tem um após ele
 * Cria cell até ali, dá free.
 * Repete o laço da onde acabou.
 */
t_cell	*divide_prompt(t_info *info)
{
	char	**mtx_str;
	t_cell	*list_cells;

	list_cells = NULL;
	mtx_str = ft_split(info->prompt, ' ');
	while (*mtx_str)
	{
		// Caracter especial
		if ((ft_strchr(*mtx_str, '|'))
			|| (ft_strchr(*mtx_str, '<'))
			|| (ft_strchr(*mtx_str, '>')))
			split_and_create(&list_cells, *mtx_str);
		// Palavra normal
		else
			create_new_cell(&list_cells, *mtx_str);
		mtx_str++;
	}
	return (list_cells);
}
