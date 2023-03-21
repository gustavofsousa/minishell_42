/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:57:41 by gusousa           #+#    #+#             */
/*   Updated: 2023/03/20 20:42:58 by parnaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	dup_or_join_char(t_cell **list, char c)
{
	if ((*list)->content == NULL)
		(*list)->content = ft_strdup_char(c);
	else
		ft_strjoin_char((*list)->content, c);
}

int	get_value_env(t_info info, t_cell **list,  char *str, int i)
{	
	int	len;
	int	line;
	char *new_value;

	i++;
	if (str[i] == '\0')
		return (0);
	len = 1;
	while ((str[i + len] == '_' || ft_isalnum(str[i + len])) && str[i + len])
		len++;
	line = -1;
	while (info.env_cpy[++line])
	{
		if (!ft_strncmp(str+1, info.env_cpy[line], len))
		{
			// Acho que problema está aqui
			printf("Minha linha: %s\n", info.env_cpy[line]);
			new_value = info.env_cpy[line] + (len + 1);
			printf("%s\n", new_value);
			break ;
		}
	}
	if ((*list)->content == NULL)
		(*list)->content = ft_strdup(new_value);
	else
		ft_strjoin_free((*list)->content, new_value);
	return (len - 1);
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
	return (0);
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
			if (str[i + 1] == ' ')
				dup_or_join_char(list, ' ');
			else
				i += get_value_env(info, list, str, i) + 1;
			if (str[i] == '\0')
				break ;
		}
		else
			dup_or_join_char(list, str[i]);
	}
}

void	expand_variable(t_cell **list_cell, t_info info)
{
	t_cell	*list_move;

	list_move = *list_cell;
	while (list_move != NULL)
	{
		if (ft_strchr(list_move->content, '$'))
		{
		printf("first while\n");
			substitute(&list_move, info, list_move->content);
		}
		list_move = list_move->next;
	}
}
