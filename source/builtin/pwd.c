/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parnaldo <parnaldo@student.42.rio >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 17:17:39 by gusousa           #+#    #+#             */
/*   Updated: 2023/02/21 10:21:56 by parnaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_pwd()
{
	char	*path;
	int		nbr_child;

	nbr_child = fork();
	if (nbr_child == 0)
	{
		path = getcwd(NULL, 0);
		printf("%s\n", path);//Talvez não printf.
		free(path);
		exit(0);
	}
}
