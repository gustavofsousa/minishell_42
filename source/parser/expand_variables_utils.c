/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parnaldo <parnaldo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 11:23:25 by parnaldo          #+#    #+#             */
/*   Updated: 2023/03/25 18:05:33 by parnaldo         ###   ########.fr       */
/*   Updated: 2023/03/13 16:19:39 by parnaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_cpychar_noprint(char *str)
{
	char	*my_str;
	int		len;
	int		i;

	my_str = NULL;
	if (str == NULL)
		len = 1;
	else
		len = ft_strlen(str);
	my_str = malloc(sizeof(char) * (len + 1));
	i = 0;
	while (i < len)
		my_str[i++] = 1;
	my_str[i] = '\0';
	return (my_str);
}

void	dup_or_join_char(t_cell **list, char c)
{
	if ((*list)->content == NULL)
		(*list)->content = ft_strdup_char(c);
	else
		(*list)->content = ft_strjoin_char((*list)->content, c);
}

void	dup_or_join_string(t_cell **list, char *new_value)
{
	if (new_value == NULL)
		return ;
	if ((*list)->content == NULL)
		(*list)->content = ft_strdup(new_value);
	else
		(*list)->content = ft_strjoin_free((*list)->content, new_value);
}

int	cpy_str(t_cell **list, char *str, int i)
{
	i = 0;
	if (str[i + 1] == '"')
		return (i);
	while (str[i])
	{
		dup_or_join_char(list, str[i]);
		i++;
	}
	return (i);
}

int	is_variable(char *str, char *env, int len_str, int i)
{
	int	len_env;

	(void) i;
	len_env = ft_strlen_env(env);
	if (!ft_strncmp(str, env, len_str) && len_str == len_env)
		return (1);
	return (0);
}
