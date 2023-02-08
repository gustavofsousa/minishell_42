/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 15:46:15 by gusousa           #+#    #+#             */
/*   Updated: 2023/02/08 14:44:40 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	g_status = 0;

int	is_numeric(char *str)
{
	return (1);
}

int	count_arg_exit(char *str)
{
	return (1);
}

void	ft_exit(char *str)
{
	int	nbr_child;
	int	id;
	
	if (count_arg_exit(str) > 1)
	{
		if (is_numeric(str))
		{
				// criar fork.
				id = ft_atoi(str);
				g_status = id;
				ft_putstr_fd("exit\n", 1);
				exit(id);
		}
	}
	else
	{
		ft_putstr_fd("exit\n", 1);
		exit(0);
	}
}
