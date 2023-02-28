/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 15:46:15 by gusousa           #+#    #+#             */
/*   Updated: 2023/02/28 20:15:22 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	g_status = 0;

int	is_numeric(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (!(ft_isdigit(*str)))
			return (0);
		str++;
	}
	return (1);
}

int	count_words(char *str)
{
	int	i;
	int	qtd_word;

	if (str == NULL)
		return (0);
	i = 0;
	qtd_word = 1;
	while (str[i + 1])
	{
		if (str[i] != ' ' && str[i + 1] == ' ')
			qtd_word++;
		i++;
	}
	return (qtd_word);
}

void	ft_exit(char *str)
{
	long long int	id;
	int				qtd_exit;
	
	qtd_exit = count_words(str);
	// sem argumento.
	if (qtd_exit == 0)
	{
		ft_putstr_fd("exit\n", 1);
		exit(0);
	}
	// 1 argumento.
	else if (qtd_exit == 1)
	{
		if (is_numeric(str))
		{
			id = ft_atoi(str);
			g_status = id;
			ft_putstr_fd("exit\n", 1);
			exit(id);
		}
		else
		{
			ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd(" numeric argument required\n", 2);
			g_status = 255;
			exit(255);
		}

	}
	// Mais de 1 argumento.
	else
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("exit: too many arguments\n", 2);
		g_status = 1;
	}
}
