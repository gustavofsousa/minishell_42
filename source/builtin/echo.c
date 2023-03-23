/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parnaldo <parnaldo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 19:54:17 by parnaldo          #+#    #+#             */
/*   Updated: 2023/03/23 17:57:35 by gusousa          ###   ########.fr       */
/*   Updated: 2023/03/04 09:57:42 by gusousa          ###   ########.fr       */
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

void	ft_echo(char *str, int fd)
{
	char	*ready_str;

	if (str == NULL)
	{
		ft_putstr_fd("\n", 1);
		return ;
	}
	ready_str = reduce_flag(str);
	ft_putstr_fd(ready_str, fd);
	free(ready_str);
	g_status = 0;
}
