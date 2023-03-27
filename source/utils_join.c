/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_join.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:28:59 by gusousa           #+#    #+#             */
/*   Updated: 2023/02/27 16:34:04 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*new_string;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	new_string = malloc(len_s1 + len_s2 + 1);
	if (!new_string)
		return (NULL);
	ft_strlcpy(new_string, s1, len_s1 + 1);
	ft_strlcat(new_string, s2, len_s1 + len_s2 + 1);
	free(s1);
	return (new_string);
}

char	*ft_strjoin_char(char *s1, char c)
{
	size_t	len_s1;
	char	*new_string;

	if (!s1 || c == '\0')
		return (NULL);
	len_s1 = ft_strlen(s1);
	new_string = malloc(len_s1 + 2);
	if (!new_string)
		return (NULL);
	ft_strlcpy(new_string, s1, len_s1 + 1);
	free(s1);
	new_string[len_s1] = c;
	new_string[len_s1 + 1] = '\0';
	return (new_string);
}
