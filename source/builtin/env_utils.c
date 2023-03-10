/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parnaldo <parnaldo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 12:09:06 by parnaldo          #+#    #+#             */
/*   Updated: 2023/03/10 12:57:35 by parnaldo         ###   ########.fr       */
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

int	check_is_status(char *content)
{
	int len;

	len = ft_strlen(content);
	if (ft_strnstr(content, "$?", len))
		return (1);
	return (0);
}

int	created_status(t_cell *list)
{
	int len_list;
	char *num;
	int len_gstatus;
	char *new_str;
	int	i;
	int len_new_str;
	//Preciso pegar o tamanho da list, saber se tem aspas simples, duplas ou simple e dupla
	len_gstatus = 0;
	len_list = ft_strlen((*list).content);
	i = 0;
	len_new_str = 0;
	//pegar o tamanho do gstatus, passar para itoa
	num = ft_itoa(g_status);
	len_gstatus = ft_strlen(num);
	printf("%d\n", g_status);
	//criar uma nova string, copiar até $ e depois passar $?, copiar o retorno da itoa copiar o restoi
	while ((*list).content[i])
	{
		if ((*list).content[i] != '$' && (*list).content[i] != '?')
			len_new_str++;
		i++;
	}
	printf("%d\n", len_gstatus);
	(void) new_str;
	//free no retorno do itoa
	//free list->content
	//\0 no final da nova string
	return (0);
}
