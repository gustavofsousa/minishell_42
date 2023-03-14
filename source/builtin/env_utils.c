/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parnaldo <parnaldo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 12:09:06 by parnaldo          #+#    #+#             */
/*   Updated: 2023/03/13 14:32:54 by parnaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_strlen_env(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=')
		i++;
	return (i);
}

int	is_equal_env(char *arg, char **env)
{
	int	counter;
	int	len_env;

	counter = 0;
	len_env = 0;
	while (env[counter])
	{
		len_env = ft_strlen_env(arg);
		if (!ft_strncmp(arg, env[counter], len_env))
		{
			free(env[counter]);
			env[counter] = ft_strdup(arg);
			return (1);
		}
		counter++;
	}
	return (0);
}

int	check_is_status(char *content)
{
	int	len;

	len = ft_strlen(content);
	if (ft_strnstr(content, "$?", len))
		return (1);
	return (0);
}

void	created_content(t_cell *list, char *str, char *num)
{
	int	index;
	int	count;
	int	len_gstatus;

	index = 0;
	count = 0;
	len_gstatus = 0;
	while ((*list).content[index] != '$')
	{
		str[index] = (*list).content[index];
		index++;
	}
	count = index + 2;
	while (num[len_gstatus])
	{
		str[index] = num[len_gstatus];
		len_gstatus++;
		index++;
	}
	while ((*list).content[count])
		str[index++] = (*list).content[count++];
	str[index] = '\0';
	free(num);
}

int	created_status(t_cell *list)
{
	int		len_list;
	char	*new_str;
	int		i;
	int		len_new_str;
	char	*num;

	len_list = ft_strlen((*list).content);
	i = 0;
	len_new_str = 0;
	num = ft_itoa(g_status);
	while ((*list).content[i])
	{
		if ((*list).content[i] != '$' && (*list).content[i+1] != '?')
			len_new_str++;
		if ((*list).content[i] == '$')
			i += 2;	
		else
			i++;
	}
	new_str = malloc((len_new_str + ft_strlen(num)) * sizeof(char));
	created_content(list, new_str, num);
	free((*list).content);
	(*list).content = new_str;
	return (0);
}
