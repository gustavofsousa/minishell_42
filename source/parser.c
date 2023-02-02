/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 13:40:15 by gusousa           #+#    #+#             */
/*   Updated: 2023/02/02 15:58:33 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	create_new_cell(char *str)
{

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
 * 2. Entre duas palavras
 * 3. Final da palavra.
 * Podendo ser duplo ou não o 2 e 3.
 * Preciso de
 * Uma função que identifique (com comando de unico ou duplo)
 * onde está na palavra
 */
void	split_and_create(char *str, char c)
{
	int	len;
	char	*new_word;

	n_times = count_recurrence(str, c);
	if (c == '|' && n_times == 1)
		find_where(str, c, n_times);
	else if (c == '|' && n_times == 2)
		printf("Error for 2 pipes") //error here.
	else if (c == '<' && n_times == 1)
		find_where(Str, c, n_times);
	else if (c == '<' && n_times == 2)
		find_where(str, c, n_times);
	else if (c == '>' && n_times == 1)
		find_where(str, c, n_times);
	else if (c == '>' && n_times == 2)
		find_where(str, c, n_times);
	else 
		printf("Error com mais de 2 <<>>?") //error here

	// O | está sozinho.
	if (*str == c && *(str + 1) == '\0')
		create_new_cell(ft_strchr(str, c));
	// O | está no fim da linha.
	else if (*str != c)

	// Vejo se tem alguma palavra antes do char c e crio célula.
	len = 0;
	while (str[len] != '\0' && str[len] != c)
		len++;
	if (len > 0)
	{
		new_word = ft_substr(str, 0, len + 1);
		create_new_cell(new_word);
		free(new_word);
	}
	// Crio célula com o que achei no char c.
	create_new_cell(ft_strchr(str, c));
}

/*
 * Função para dividir as palavras do prompt em nós de uma lista.
 */
void	divide_prompt(t_info *info)
{
	char	**mtx_str;

	// Eu preciso achar se tem algum caracter especial
	// Depois verifico se ele está na frente ou atrás
	// Verifico se ele é duplo ou sozinho
	// Crio subtrings com eles separados
	// Tenho que procurar no inicio, meio e fim de string.
	mtx_str = ft_split(info->prompt, ' ');
	while (*mtx_str)
	{
		Caracter especial
		if (ft_strchr(*str, '|' ))
			split_and_create(*str, '|');
		else if (ft_strchr(*str, '<'))
			split_and_create(*str, '<');
		else if (ft_strchr(*str, '>'))
			split_and_create(*str, '>');
		// Palavra normal
		else
			create_new_cell(*str);
		mtx_str++;
	}
}
