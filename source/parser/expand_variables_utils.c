/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parnaldo <parnaldo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 11:23:25 by parnaldo          #+#    #+#             */
/*   Updated: 2023/03/22 15:16:27 by parnaldo         ###   ########.fr       */
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
