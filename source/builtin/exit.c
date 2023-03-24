/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 15:46:15 by gusousa           #+#    #+#             */
/*   Updated: 2023/03/24 11:35:19 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_numeric(char *str)
{
	char	*num;

	num = ft_itoa(ft_atoi(str));
	if (ft_strncmp(num, str, ft_strlen(str)))
	{
		free(num);
		return (0);
	}
	free(num);
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

void	exit_with_args(char *str, int id, int fd)
{
	if (is_numeric(str))
	{
		g_status = id;
		ft_putstr_fd("exit\n", fd);
		exit(id);
	}
	else
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(" numeric argument required\n", 2);
		g_status = 255;
		exit(255);
	}
}

void	ft_exit(char *str, int fd)
{
	int				qtd_args;

	qtd_args = count_words(str);
	if (qtd_args == 0)
	{
		ft_putstr_fd("exit\n", fd);
		exit(0);
	}
	else if (qtd_args == 1)
	{
		exit_with_args(str, ft_atoi(str), fd);
	}
	else if (qtd_args > 1)
	{
		ft_putstr_fd("exit\nexit: too many arguments\n", 2);
		g_status = 1;
	}
}
