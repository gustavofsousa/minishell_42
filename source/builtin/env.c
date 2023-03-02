/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parnaldo <parnaldo@student.42.rio >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 08:10:50 by parnaldo          #+#    #+#             */
/*   Updated: 2023/03/02 09:41:36 by parnaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**ft_cpy_env(char **envs)
{
	int		len;
	char	**cpy_envs;

	len = 0;
	while (envs[len])
		len++;
	cpy_envs = malloc((len + 1) * sizeof(char *));
	if (!cpy_envs)
		return (NULL);
	len = 0;
	while (envs[len])
	{
		cpy_envs[len] = ft_strdup(envs[len]);
		len++;
	}
	cpy_envs[len] = NULL;
	return (cpy_envs);
}

int	ft_env(char **envs)
{
	int	i;

	i = 0;
	if (!envs)
	{
		printf("env:");
		return (0);
	}
	while (envs[i])
	{
		printf("%s\n", envs[i]);
		i++;
	}
	return (1);
}
