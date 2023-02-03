/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 13:40:15 by gusousa           #+#    #+#             */
/*   Updated: 2023/02/03 10:24:29 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
void	create_new_cell(char *str)
{

}
*/

//crio nó até ele, com ele, depois dele;
void	create_three_cells(char *str, char set, int n_times)
{
	char	*first_word;
	char	*second_word;
	char	*third_word;
	int		len_first;

	len_first = 0;
	while (str[len_first] != set)
		len_first++;
	first_word = ft_substr(str, 0, len_first + 1);
	second_word = ft_substr(str, len_first, n_times + 1);
	third_word = ft_substr(str, len_first + n_times, ft_strlen(str));
	//create_new_cell(first_word);
	//create_new_cell(second_word);
	//create_new_cell(third_word);
	printf("Célula criada->\t%s\n", first_word);
	printf("Célula criada->\t%s\n", second_word);
	printf("Célula criada->\t%s\n", third_word);
	free(first_word);
	free(second_word);
	free(third_word);
}

// crio nó até achar ele, e a partir dele;
void	create_two_cells_end(char *str, int n_times)
{
	char	*first_word;
	char	*second_word;

	first_word = ft_substr(str, 0, ft_strlen(str) - n_times);
	second_word = ft_substr(str, ft_strlen(str) - 1 - n_times, n_times);
	//create_new_cell(first_word);
	//create_new_cell(second_word);
	printf("Célula criada->\t%s\n", first_word);
	printf("Célula criada->\t%s\n", second_word);
	free(first_word);
	free(second_word);
}

// crio nó com ele e resto;
void	create_two_cells_begin(char *str, int n_times)
{
	char	*first_word;
	char	*second_word;

	first_word = ft_substr(str, 0, n_times);
	second_word = ft_substr(str, n_times, ft_strlen(str));
	printf("Célula criada->\t%s\n", first_word);
	printf("Célula criada->\t%s\n", second_word);
	//create_new_cell(first_word);
	//create_new_cell(second_word);
	free(first_word);
	free(second_word);
}

void	find_where(char *str, char set, int n_times)
{

	// Vejo se está no início
	if (*str == set)
		create_two_cells_begin(str, n_times);
	// Vejo se está no fim
	else if (str[ft_strlen(str) - 1])
		create_two_cells_end(str, n_times);
	// No meio
	else
		create_three_cells(str, set, n_times);
}

int	count_recurrence(char *str, char set)
{
	int	n_times;

	n_times = 0;
	while (*str)
		if (*str++ == set)
			n_times++;
	return (n_times);
}

/*
 * As três opções para crtce especial é:
 * 1. Início da palavra
 * 2. Entre duas palavras. Pode ser duplo.
 * 3. Final da palavra. Pode ser duplo.
 */
void	split_and_create(char *str, char c)
{
	int	n_times;

	n_times = count_recurrence(str, c);
	if (c == '|' && n_times == 1)
		find_where(str, c, n_times);
	else if (c == '|' && n_times == 2)
		printf("Error for 2 pipes"); //error here.
	else if (c == '<' && n_times == 1)
		find_where(str, c, n_times);
	else if (c == '<' && n_times == 2)
		find_where(str, c, n_times);
	else if (c == '>' && n_times == 1)
		find_where(str, c, n_times);
	else if (c == '>' && n_times == 2)
		find_where(str, c, n_times);
	else 
		printf("Error com mais de 2 <<>>?"); //error here

}

void	split_and_create(char *str)
{
	char	*new_word;

	while (*str)
	{
		if (*str == '|' || *str == '>' || *str == '<')
		{
			if (*(str + 1) == *str)
			{
				new_word = ft_substr(str, 0, 3);
				str++;
			}
			else
				new_word = ft_substr(str, 0, 2);
			//create_new_cell(new_word);
			printf("New cell->\t%s", new_word);
			free(new_word);
		}
		str++;
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
void	divide_prompt(t_info *info)
{
	char	**mtx_str;

	mtx_str = ft_split(info->prompt, ' ');
	while (*mtx_str)
	{
		// Caracter especial
		if (ft_strchr(*mtx_str, '|')
				|| (ft_strchr(*mtx_str, '<')
				|| (ft_strchr(*mtx_str, '>'))
			split_and_create(*mtx_str);
		// Palavra normal
		else
			printf("Célula criada->\t%s\n", *mtx_str);
			//create_new_cell(*str);
		mtx_str++;
	}
}
