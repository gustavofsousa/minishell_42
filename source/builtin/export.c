/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parnaldo <parnaldo@student.42.rio >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 20:54:12 by parnaldo          #+#    #+#             */
/*   Updated: 2023/03/24 11:23:31 by parnaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_arg(char *arg)
{
	int	i;
	int	is_equals;

	i = 0;
	is_equals = 0;
	if (ft_isdigit(arg[i]))
		return (0);
	while (arg[i])
	{
		if (arg[i] == '=')
			is_equals = 1;
		i++;
	}
	if (!is_equals)
		return (0);
	return (1);
}

static char	**created_new_env(struct s_info *info, int amount_args)
{
	char	**new_env;
	int		i;

	i = 0;
	while (info->env_cpy[i])
		i++;
	i += amount_args;
	new_env = malloc((i + 1) * sizeof(char *));
	if (!new_env)
		return (NULL);
	new_env[i] = NULL;
	return (new_env);
}

static void	cpy_args(int i, int amount_args, char **new_env, char **args)
{
	int	count;

	count = 0;
	while (count < amount_args)
	{
		if (check_arg(args[count]))
		{
			new_env[i] = ft_strdup(args[count]);
			i++;
		}
		count++;
	}
	new_env[i] = NULL;
}

static void	replace_env(struct s_info *info, char **args, int amount_args)
{
	char	**new_env;
	int		i;

	i = 0;
	new_env = created_new_env(info, amount_args);
	if (!new_env)
		return ;
	while (info->env_cpy[i])
	{
		new_env[i] = ft_strdup(info->env_cpy[i]);
		free(info->env_cpy[i]);
		i++;
	}
	free(info->env_cpy);
	cpy_args(i, amount_args, new_env, args);
	info->env_cpy = new_env;
}

int	ft_export(char *arg, struct s_info *info)
{
	char	**args;
	int		new_envs;
	int		i;

	if (!arg)
		return (0);
	new_envs = 0;
	i = 0;
	args = ft_split(arg, ' ');
	while (args[i])
	{
		if (check_arg(args[i]) && !is_equal_env(args[i], info->env_cpy))
			new_envs++;
		else if (!check_arg(args[i])) 
			print_err_export(args[i]);
		i++;
	}
	replace_env(info, args, new_envs);
	i = 0;
	while (args[i])
		free(args[i++]);
	free(args);
	g_status = 0;
	return (0);
}
