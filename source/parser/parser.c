/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 13:40:15 by gusousa           #+#    #+#             */
/*   Updated: 2023/03/27 17:44:51 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	copy_to_cell(t_cell **list_cells, char *str)
{
	char	*new_word;
	int		space;
	int		i;

	space = 0;
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

void	split_and_create(t_cell **list_cells, char *str)
{
	int		i;
	char	*new_word;

	while (*str)
	{
		i = 0;
		if (*str == '|' || *str == '>' || *str == '<')
			i = copy_to_cell(list_cells, str);
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

int	has_metadado_together(char *str)
{
	if (ft_strchr(str, '|') || ft_strchr(str, '<') || ft_strchr(str, '>'))
		return (1);
	return (0);
}

void	set_free_mtx(char **mtx_str)
{
	int		i;

	if (mtx_str)
	{
		i = -1;
		while (mtx_str[++i])
			free(mtx_str[i]);
		free (mtx_str);
	}
}

int	divide_prompt(t_info *info, t_cell **list_cells)
{
	char	**mtx_str;
	int		i;
	int		fq;

	fq = 0;
	mtx_str = ft_split_mod(info->prompt, ' ', &fq);
	if (fq == 1)
	{
		ft_putstr_fd("Missing final quote\n", 2);
		return (-1);
	}
	i = 0;
	while (mtx_str[i])
	{
		if (has_metadado_together(mtx_str[i]))
			split_and_create(list_cells, mtx_str[i]);
		else
			create_new_cell(list_cells, mtx_str[i], 1);
		i++;
	}
	set_free_mtx(mtx_str);
	return (0);
}
