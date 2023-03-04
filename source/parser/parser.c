/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 13:40:15 by gusousa           #+#    #+#             */
/*   Updated: 2023/03/02 19:27:29 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 *	Verifico se tem duplo(metadado)
 *	Verifico se tem flag space
 *	Crio a nova célula.
 */
int	copy_to_cell(t_cell **list_cells, char *str)
{
	char	*new_word;
	int		space;
	int		i;

	space = 0;
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
	if (*(str + i) == '\0')
		space = 1;
	create_new_cell(list_cells, new_word, space);
	free(new_word);
	return (i);
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
	char	*new_word;

	while (*str)
	{
		i = 0;
		// Copiar o metadado, duplo ou normal
		if (*str == '|' || *str == '>' || *str == '<')
		{
			i = copy_to_cell(list_cells, str);
		}
		// Copiar palavra normal
		else
		{
			while (str[i] != '|' && str[i] != '>'
				&& str[i] != '<' && str[i] != '\0')
				i++;
			new_word = ft_substr(str, 0, i);
			if (*(str + i) == '\0')
				create_new_cell(list_cells, new_word, 1);
			else
				create_new_cell(list_cells, new_word, 0);
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
