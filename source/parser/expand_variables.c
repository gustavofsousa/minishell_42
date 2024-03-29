/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:57:41 by gusousa           #+#    #+#             */
/*   Updated: 2023/03/27 17:43:59 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_excpt(t_cell **list, char *str, int i)
{
	char	*tmp;

	if (str[i] == '\0')
		return (0);
	if (str[i] == '?')
	{
		tmp = ft_itoa(g_status);
		dup_or_join_string(list, tmp);
		free (tmp);
		return (1);
	}
	return (48);
}

int	get_value_env(t_info info, t_cell **list, char *str, int i)
{	
	int		len;
	int		line;
	char	*new_value;

	if (str[i] == '\0' || str[i] == '?')
		return (handle_excpt(list, str, i));
	new_value = NULL;
	len = 0;
	while ((str[i + len] == '_' || ft_isalnum(str[i + len])) && str[i + len])
		len++;
	line = -1;
	while (info.env_cpy[++line])
	{
		if (is_variable(str + i, info.env_cpy[line], len, i))
		{
			new_value = info.env_cpy[line] + (len + 1);
			dup_or_join_string(list, new_value);
			return (len);
		}
	}
	new_value = ft_cpychar_noprint(new_value);
	dup_or_join_string(list, new_value);
	free(new_value);
	return (len);
}

int	change_flag_quote(char c, int fq)
{
	if (fq == 0)
	{
		if ('"' == c)
			return (2);
		else if (c == '\'')
			return (1);
	}
	else if (fq == 1)
	{
		if (c == '\'')
			return (0);
	}
	else if (fq == 2)
	{
		if (c == '"')
			return (0);
	}
	return (fq);
}

void	substitute(t_cell **list, t_info info, char *str)
{	
	int		fq;
	int		i;

	free((*list)->content);
	(*list)->content = NULL;
	i = -1;
	fq = 0;
	while (str[++i])
	{
		fq = change_flag_quote(str[i], fq);
		if (fq != 1 && str[i] == '$')
		{
			i = deal_with_dollar(list, info, str, i);
			if (str[i] == '\0')
				break ;
		}
		else if (fq == 1)
			dup_or_join_char(list, str[i]);
		else
			dup_or_join_char(list, str[i]);
	}
	free(str);
	str = NULL;
}

void	expand_variable(t_cell **list_cell, t_info info)
{
	t_cell	*list_move;

	list_move = *list_cell;
	while (list_move != NULL && list_move->content != NULL)
	{
		if (ft_strchr(list_move->content, '$'))
			substitute(&list_move, info, ft_strdup(list_move->content));
		list_move = list_move->next;
	}
}
