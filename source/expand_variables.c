/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:57:41 by gusousa           #+#    #+#             */
/*   Updated: 2023/03/07 14:15:26 by parnaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
 * Apaga onde estava o nome da variável e coloca o valor dela.
 */

int	len_word(char *str)
{
	int	start;
	int	end;

	start = 0;
	end = 0;
	if (!str)
		return (-1);
	while (str[start] != '$')
		start++;
	end = start;
	while ((str[end] != 34 && str[end] != 39) && str[end])
		end++;
	return (end - start);
}

void	create_new_content(t_cell **list, t_info info, int index, int len_w)
{	
	int		aux;
	int		i;
	char	*str;

	str = malloc(len_new_content * sizeof(char));
	while ((*list)->content[i] != '$')
	{
		str[i] = (*list)->content[i];
		i++;
	}
	aux = i + (len_w + 1);
	//free na list->content
	while (info.env_cpy[index][++len_w])
		str[i++] = info.env_cpy[index][len_w];
	while ((*list)->content[aux])
		str[i++] = (*list)->content[aux++];
	str[i] = '\0';
	free((*list)->content);
	(*list)->content = NULL;
	(*list)->content = str;
}

void	substitute(t_cell **list, t_info info, int index)
{
	int		len_content;
	int		len_w;
	int		len_new_content;

	len_content = 0;
	len_w = 0;
	len_new_content = 0;
	while (info.env_cpy[index][len_w] != '=')
		len_w++;
	len_content = ft_strlen((*list)->content) - (len_w + 1);
	len_new_content = ft_strlen(info.env_cpy[index]) - len_w;
	len_new_content += len_content;
	create_new_content(list, info, index, len_w);
}
/*
 * Compara se depois do $ a variável está com nome igual.
 */
int	look_for_variable(t_cell *list, t_info info)
{
	int		index;
	char	*str;
	char	*str_env;
	int		len;
	int		len_w;

	len = 0;
	len_w = 0;
	index = 0;
	str = list->content;
	len_w = len_word(str);
	while (str[index] != '$')
		index++;
	str_env = ft_substr(str, index, len_w);
	index = 0;
	while (info.env_cpy[index])
	{
		len = ft_strlen(str_env + 1);
		if (!ft_strncmp(str_env + 1, info.env_cpy[index], len))
			return (index);
		index++;
	}
	free(str_env);
	return (1);
}

void	expand_variable(t_cell **list_cell, t_info info)
{
	t_cell	*list_move;
	int		index;

	index = 0;
	list_move = *list_cell;
	while (list_move != NULL)
	{
		//vai ter duas condições e a com aspas
		if (ft_strchr(list_move->content, '$'))
		{
			if (ft_strchr(list_move->content, 39))
				if (ft_strnstr(list_move->content, "'\"", 3)
					|| (ft_strchr(list_move->content, 39)
						&& !ft_strchr(list_move->content, 34)))
					break ;
			index = look_for_variable(list_move, info);
			if (index)
			{
				substitute(&list_move, info, index);
			}
		}
		list_move = list_move->next;
	}
}
