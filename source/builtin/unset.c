/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parnaldo <parnaldo@student.42.rio >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 19:07:03 by parnaldo          #+#    #+#             */
/*   Updated: 2023/02/13 16:06:40 by parnaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**created_env(struct s_info *info)
{
	int i;

	i = 0;
	(void) info;
	//while (info->env_cpy[i])
	return (NULL);
}

int	ft_unset(char *arg, struct s_info *info)
{
	int			i;
	int			j;
	char		**variables;

	(void) info;
	i = 0;
	j = 0;
	variables = ft_split(arg, ' ');
	if (!variables)
		return (0);
	/*while (variables[i])
	{
		//while (info->env_cpy)
	}
	*/
	i = 0;
	while (variables[i])
		free(variables[i++]);
	return (1);
}
