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

/*static char	**created_env(struct s_info *info)
{
	int i;

	(void)i;
	(void) info;
	//while (info->env_cpy[i])
	return (NULL);
}*/

static int	ft_strlen_env(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=')
		i++;
	return (i);
}

int	ft_unset(char *arg, struct s_info *info)
{
	int			i;
	int			counter;
	int			len_var;
	int			len_env;
	char		**variables;
	
	i = 0;
	counter = 0;
	len_var = 0;
	len_env = 0;
	variables = ft_split(arg, ' ');
	if (!variables)
		return (0);
	while (info->env_cpy[i])
	{
			counter = 0;
			while (variables[counter])
			{
				len_var = ft_strlen(variables[counter]);
				len_env = ft_strlen_env(info->env_cpy[i]);
				//printf("%s\n", variables[counter]);
				//printf("%s\n", info->env_cpy[i]);
				if (!ft_strncmp(info->env_cpy[i], variables[counter], len_env) && len_env == len_var)
				{
					printf("OLAAaaaaa\n");
				}
				counter++;
			}
		i++;
	}
	i = 0;
	while (variables[i])
		free(variables[i++]);
	puts("estoy aka!");
	return (1);
}
