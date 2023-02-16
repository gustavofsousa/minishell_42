/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parnaldo <parnaldo@student.42.rio >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 19:07:03 by parnaldo          #+#    #+#             */
/*   Updated: 2023/02/16 16:12:02 by parnaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
				if (!ft_strncmp(info->env_cpy[i], args[counter], len_env) && len_env == len_var)
					len++;
				counter++;
			}
		i++;
	}
	return (i - len);
}

static int	is_equal(char **args, char *str)
{
	int counter;
	int	len_var;
	int	len_env;

	counter = 0;
	len_var = 0;
	len_env = 0;
	while (args[counter])
	{
		len_var = ft_strlen(args[counter]);
		len_env = ft_strlen_env(str);
		if (!ft_strncmp(str, args[counter], len_env) && len_env == len_var)
			return (1);
		counter++;
	}
	return (0);
}

int	ft_unset(char *arg, struct s_info *info)
{
	int			i;
	char		**variables;
	int			len_envs;
	char		**new_env;

	i = 0;
	len_envs = 0;
	variables = ft_split(arg, ' ');
	if (!variables)
		return (0);
	len_envs = len_new_env(info, variables);	
	new_env = malloc(sizeof(char *) * (len_envs + 1));
	if(!new_env)
		return (0);
	while (info->env_cpy[i])
	{
		if(!is_equal(variables, info->env_cpy[i]))
		{
			new_env[i] = ft_strdup(info->env_cpy[i]);
			printf("-> cpy == %s\n", new_env[i]);
		}
		//verificar vazamento, faço o malloc de +1 para poder adicionar mais fácil
		i++;
		free(info->env_cpy[i]);
	}
	free(info->env_cpy);
	new_env[i++] = NULL;
	info->env_cpy = new_env;
	//printf("%s\n", new_env[30]);
	i = 0;
	while (variables[i])
		free(variables[i++]);
	return (1);
}
