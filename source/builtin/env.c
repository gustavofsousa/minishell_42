/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parnaldo <parnaldo@student.42.rio >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 08:10:50 by parnaldo          #+#    #+#             */
/*   Updated: 2023/02/12 20:48:02 by parnaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_env(void)
{
	extern char	**environ;
	int			i;

	i = 0;
	if (!environ)
		return (0);
	while (environ[i])
		printf("%s\n", environ[i++]);
	return (1);
}
