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

static int len_new_env(struct s_info *info, char **args)
{
	int	i;
	int	counter;
	int len_env;
	int len_var;
	int	len;

	len = 0;
	len_env = 0;
	len_var = 0;
	i = 0;
	counter = 0;
	while (info->env_cpy[i])
	{
			counter = 0;
			while (args[counter])
			{
				len_var = ft_strlen(args[counter]);
				len_env = ft_strlen_env(info->env_cpy[i]);
				if (ft_strncmp(info->env_cpy[i], args[counter], len_env) && len_env == len_var)
							len++;
				counter++;
			}
		i++;
	}
	return (len);
}

int	ft_unset(char *arg, struct s_info *info)
{
	int			i;
	char		**variables;
	int			len_envs;

	i = 0;
	len_envs = 0;
	variables = ft_split(arg, ' ');
	if (!variables)
		return (0);
	len_envs = len_new_env(info, variables);
	printf("len %d\n", len_envs);
	while (variables[i])
		free(variables[i++]);
	return (1);
}
