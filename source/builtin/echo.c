/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parnaldo <parnaldo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 19:54:17 by parnaldo          #+#    #+#             */
/*   Updated: 2023/02/07 15:56:43 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*reduce_flag(char *str)
{
	int	i;

	while (*str)
	{
		i = 1;
		//printf("%s\n", str);
		if (*str == '-')
		{
			while (*(str + i) == 'n')
				i++;
			if (*(str + i) != ' ' && (*(str + i) != '\0'))
				return (ft_strdup(str));
		}
		if (!ft_strchr(str, '-'))
			return (ft_strdup(str));
		str += i;
	}
	if (*str == '\0')
		return (ft_strdup(""));
	return (NULL);
}

void    ft_echo(char *str)
{
	int		nbr_child;
	char	*ready_str;

	nbr_child = fork();
	if (nbr_child == 0)
	{
		ready_str = reduce_flag(str);
		printf("%s\n", ready_str);
		free(ready_str);
		exit(0);
	}
}
