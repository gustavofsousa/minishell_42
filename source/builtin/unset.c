/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parnaldo <parnaldo@student.42.rio >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 19:07:03 by parnaldo          #+#    #+#             */
/*   Updated: 2023/03/02 10:03:01 by parnaldo         ###   ########.fr       */
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

static int	is_equal(char **args, char *str)
{
	int	counter;
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

static int	len_new_env(struct s_info *info, char **args)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (info->env_cpy[i])
	{
		if (!is_equal(args, info->env_cpy[i]))
			len++;
		i++;
	}
	return (len);
}

static void	cpy_variable(struct s_info *info, char **args, char **new_env)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (info->env_cpy[i])
	{
		if (!is_equal(args, info->env_cpy[i]))
		{
			new_env[count] = ft_strdup(info->env_cpy[i]);
			count++;
		}
		free(info->env_cpy[i]);
		i++;
	}
	free(info->env_cpy);
	new_env[count] = NULL;
}

int	ft_unset(char *arg, struct s_info *info)
{
	int			i;
	char		**args;
	int			len_envs;
	char		**new_env;
	int			count;

	count = 0;
	i = 0;
	len_envs = 0;
	if (!arg)
		return (0);
	args = ft_split(arg, ' ');
	len_envs = len_new_env(info, args);
	new_env = malloc((len_envs + 1) * sizeof(char *));
	if (!new_env)
		return (0);
	cpy_variable(info, args, new_env);
	info->env_cpy = new_env;
	return (1);
}
