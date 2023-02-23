/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parnaldo <parnaldo@student.42.rio >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 21:44:56 by parnaldo          #+#    #+#             */
/*   Updated: 2023/02/23 15:14:27 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int ft_cd(char *path, struct s_info info)
{
	int	status;

    if (path == NULL)
	{
        // no directory provided
        ft_putstr_fd("cd: missing operand\n", 2);
        return (1);
    }

    chdir(path);
    if (status == -1)
	{
        // directory change failed
        perror("cd");
        return (1);
    }
}
