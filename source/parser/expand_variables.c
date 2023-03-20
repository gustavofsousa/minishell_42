/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:57:41 by gusousa           #+#    #+#             */
/*   Updated: 2023/03/20 18:11:07 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * Apaga onde estava o nome da variável e coloca o valor dela.
 */
void	create_new_content(t_cell **list, t_info info)
{	
	
}

void	sth()
{

}

void	trade_value(t_cell **list, t_info info, char *args)
{
	int	len_in;
	int	index_env;

	if (args[0] == '\0')
		return ;
	len_in = 0;
	while ((str[i] == '_' || ft_isalnum(str[i])) && str[i])
		len_in++; 
	new_value = get_value_env(info, args, len_in);
	if (index_env != -1)
	{
		// dup da primeira linha
		// jion_char dos env + len + 1
		// join da linha + len
	}
	else
		//substitute for space
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
		if (c == '\'')
			return (0);
	else if (fq == 2)
		if (c == '"')
			return (0);
}

void	substitute(t_cell **list, t_info info, char **args)
{	
	int		fq;
	int		i;
	int		j;

	i = -1;
	fq = 0;
	while (args[++i])
	{
		j = -1;
		while (args[i][++j])
		{
			fq = change_flag_quote(args[i][j], fq);
			if (fq != 1)
				trade_value(list, info, args[i]);
		}
	}
}
/*
 * Compara se depois do $ a variável está com nome igual.
 */

void	expand_variable(t_cell **list_cell, t_info info)
{
	t_cell	*list_move;
	char	**args;
	int		i;

	list_move = *list_cell;
	while (list_move != NULL)
	{
		if (ft_strchr(list_move->content, '$'))
		{
			args = ft_split(list_move->content, '$');
			substitute(list_move, info, args);
			i = -1;
			while (args[++i])
				free(args[i]);
			free(args);
		}
		list_move = list_move->next;
	}
}
