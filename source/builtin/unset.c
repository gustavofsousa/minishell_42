/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parnaldo <parnaldo@student.42.rio >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 19:07:03 by parnaldo          #+#    #+#             */
/*   Updated: 2023/02/12 20:53:41 by parnaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_unset(char *arg)
{
	int			i;
	char		**variables;

	i = 0;
	variables = ft_split(arg, ' ');
	if (!variables)
		return (0);
	while (variables[i])
		unsetenv(variables[i++]);
	i = 0;
	while (variables[i])
		free(variables[i++]);
	return (1);
}
