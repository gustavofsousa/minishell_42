/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parnaldo <parnaldo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 12:09:06 by parnaldo          #+#    #+#             */
/*   Updated: 2023/03/09 12:36:45 by parnaldo         ###   ########.fr       */
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

int  is_equal_env(char *arg, char **env)
 {
	    int counter;
	    int len_env;
	
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
