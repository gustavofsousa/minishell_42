/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_extra.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 15:46:15 by gusousa           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/02/09 11:06:05 by gusousa          ###   ########.fr       */
=======
/*   Updated: 2023/02/08 14:44:40 by gusousa          ###   ########.fr       */
>>>>>>> b70911a71541b2925a87d4979581b49f76c043ab
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	g_status = 0;

int	is_numeric(char *str)
{
	char	**str_mtx;

	str_mtx = ft_split(str, ' ');
	while (str[i])
	{
		j = 0;
		if (str_mtx[i][j] == '-' || str_mtx[i][j])
			j++;
		while (str_mtx[i][j])
			if (!(ft_isdigit(str_mtx[i][j++])))
				return (0);
		i++;
	}
	return (1);
}

int	count_words(char *str)
{
	int	i;
	int	qtd_word;

	i = 0;
	qtd_word = 1;
	if (str == NULL)
		return (-1);
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
	//int	nbr_child;
	long long int	id;
	int				qtd_exit;
	
	qtd_exit = count_words(str) + 1;
	if (qtd_exit > 1)
	{
		// criar fork.
		if (is_numeric(str))
		{
			id = ft_atoi(str);
			g_status = id;
			ft_putstr_fd(str, 1);
			ft_putstr_fd("\texit with id-> ", 1);
			ft_putnbr_fd(id, 1);
			ft_putstr_fd("\n", 1);
			//exit(id);
		}
		else
		{
			ft_putstr_fd(str, 1);
			ft_putstr_fd("\texit: t: numeric argument required\n", 2);
			g_status = 255;
			//exit(255);
		}
	}
	else
	{
		ft_putstr_fd(str, 1);
		ft_putstr_fd("exit with no args\n", 1);
		//exit(0);
	}
}
