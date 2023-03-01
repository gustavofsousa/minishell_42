/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 13:40:15 by gusousa           #+#    #+#             */
/*   Updated: 2023/03/01 18:08:02 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 *	Verifico se tem duplo(metadado)
 *	Verifico se tem flag space
 *	Crio a nova célula.
 */
char	*copy_to_cell(char *str, int meta)
{
	char	*new_word;
	int		space;
	int		i;

	space = 0;
	if (meta = 1)
	{
		//Se é duplo.
		if (*(str + 1) == *str && *(str + 1) != '|')
		{
			i = 2;
			new_word = ft_substr(str, 0, 2);
		}
		else
		{
			i = 1;
			new_word = ft_substr(str, 0, 1);
		}
		if (*(str + i) == ' ')
			space = 1;
	}
	new_word = ft_substr(str, 0, i);
	create_new_cell(list_cells, new_word, space);
	free(new_word);
}

/*
 * As três opções para metadado é:
 * 1. Início da palavra
 * 2. Entre duas palavras. 
 * 3. Final da palavra.
 */
void	split_and_create(t_cell **list_cells, char *str)
{
	int		i;

	new_word = NULL;
	while (*str)
	{
		i = 0;
		// Copiar o metadado, duplo ou normal
		if (*str == '|' || *str == '>' || *str == '<')
		{
			copy_to_cell();
		}
		// Copiar palavra normal
		else
		{
			while (str[i] != '|' && str[i] != '>'
				&& str[i] != '<' && str[i] != '\0')
				i++;
			copy_to_cell();
		}
		str += i;
	}
}

/*
 * Função para dividir as palavras do prompt em nós de uma lista.
 *
 * Andando em cada palavra, vendo se tem caracter
 * Se tiver, vê se tem um após ele
 * Cria cell até ali, dá free.|cat
 * Repete o laço da onde acabou.
 */
void	divide_prompt(t_info *info, t_cell **list_cells)
{
	char	**mtx_str;
	int		i;

	mtx_str = ft_split(info->prompt, ' ');
	i = 0;
	while (mtx_str[i])
	{
		// Metadado junto com palavra.
		if (ft_strchr(mtx_str[i], '|') || ft_strchr(mtx_str[i], '<')
			|| ft_strchr(mtx_str[i], '>'))
			split_and_create(list_cells, mtx_str[i]);
		// Palavra ou metadado sozinho.
		else
			create_new_cell(list_cells, mtx_str[i], 1);
		i++;
	}
	if (mtx_str)
	{
		i = -1;
		while (mtx_str[++i])
			free(mtx_str[i]);
		free (mtx_str);
	}
}
