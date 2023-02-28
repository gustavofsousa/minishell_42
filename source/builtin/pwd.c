/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parnaldo <parnaldo@student.42.rio >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 17:17:39 by gusousa           #+#    #+#             */
/*   Updated: 2023/02/28 16:17:48 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_pwd()
{
	char	*path;

	path = getcwd(NULL, 0);
	printf("%s\n", path);//Talvez não printf.
	free(path);
}
