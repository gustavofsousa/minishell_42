/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parnaldo <parnaldo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 11:23:25 by parnaldo          #+#    #+#             */
/*   Updated: 2023/03/09 14:24:18 by gusousa          ###   ########.fr       */
/*   Updated: 2023/03/13 16:19:39 by parnaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

int	calc_len_content(t_cell **list, t_info info, int index)
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
	return (len_new_content);
}

/*void	clear_variable(t_cell **list_cell)
{
	int i;

	i = 0;
	//while (list){}
	//ir até o $ de saber um substr dessa partte limpar e colocar no lulgar.
}*/
