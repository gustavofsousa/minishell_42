/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 13:40:15 by gusousa           #+#    #+#             */
/*   Updated: 2023/02/01 15:21:26 by gusousa          ###   ########.fr       */
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

	// Vejo se tem alguma palavra antes do char c e crio célula.
	len = 0;
	while (str[len] != '\0' && str[len] != c)
		len++;
	if (len > 0)
	{
		new_word = ft_substr(str, 0, len + 1);
		create_new_cell(new_word);
		free (new_word);
	}
	// Crio célula com o que achei no char c.
	create_new_cell(ft_strchr(str, c));
}

void	divide_prompt(t_info *info)
{
	char	**str;

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
