/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 18:38:23 by gusousa           #+#    #+#             */
/*   Updated: 2023/03/25 18:50:05 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	deal_with_dollar(t_cell **list, t_info info, char *str, int i)
{
	if (str[i + 1] == ' ' || str[i + 1] == '\0'
		|| str[i + 1] == 34 || str[i + 1] == 39)
		dup_or_join_char(list, '$');
	else
		i += get_value_env(info, list, str, i + 1);
	return (i);
}
