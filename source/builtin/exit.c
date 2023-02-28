/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 15:46:15 by gusousa           #+#    #+#             */
/*   Updated: 2023/02/28 20:22:48 by gusousa          ###   ########.fr       */
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

void	exit_with_args(char *str, int id)
{
	if (is_numeric(str))
	{
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

void	ft_exit(char *str)
{
	int				qtd_args;

	qtd_args = count_words(str);
	if (qtd_args == 0)
	{
		ft_putstr_fd("exit\n", 1);
		exit(0);
	}
	else if (qtd_args == 1)
	{
		exit_with_args(str, ft_atoi(str));
	}
	else if (qtd_args > 1)
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("exit: too many arguments\n", 2);
		g_status = 1;
	}
}
