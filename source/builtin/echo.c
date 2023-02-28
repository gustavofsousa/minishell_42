/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parnaldo <parnaldo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 19:54:17 by parnaldo          #+#    #+#             */
/*   Updated: 2023/02/28 16:19:48 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*create_str(char *str, int trail)
{
	if (trail == 1)
		return (ft_strdup(str));
	else
		return (ft_strjoin(str, "\n"));
}

char	*reduce_flag(char *str)
{
	int	i;
	int	trail;

	trail = 0;
	while (*str)
	{
		i = 1;
		if (*str == '-')
		{
			while (*(str + i) == 'n')
				i++;
			if (*(str + i) != ' ' && (*(str + i) != '\0'))
				return (create_str(str, trail));
			// A flag -n pode ser ativada.
			if (i > 1)
				trail = 1;
		}
		if (!ft_strchr(str, '-'))
			return (create_str(str, trail));
		str += i;
	}
	return (ft_strdup("\n"));
}

void    ft_echo(char *str)
{
	char	*ready_str;

	ready_str = reduce_flag(str);
	ft_putstr_fd(ready_str, 1); //Essa ft porque o printf espera o \n no caso de "".
	free(ready_str);
}
