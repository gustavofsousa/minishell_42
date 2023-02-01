/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 13:40:15 by gusousa           #+#    #+#             */
/*   Updated: 2023/02/01 16:22:59 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	create_new_cell(char *str)
{

}

void	split_and_create(char *str, char c)
{
	int	len;
	char	*new_word;

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
	char	**str;

	// Eu preciso achar se tem algum caracter especial
	// Depois verifico se ele está na frente ou atrás
	// Verifico se ele é duplo ou sozinho
	// Crio subtrings com eles separados
	// Tenho que procurar no iniicio, meio e fim de string.
	str = ft_split(info->prompt, ' ');
	while (*str)
	{
		// Separar os elementos
		if (ft_strchr(*str, '|' ))
			split_and_create(*str, '|');
		else if (ft_strchr(*str, '<'))
			split_and_create(*str, '<');
		else if (ft_strchr(*str, '>'))
			split_and_create(*str, '>');
		//Criar célula com cada elemento
		else
			create_new_cell(*str);
		str++;
	}
}
