/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_the_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:47:45 by gusousa           #+#    #+#             */
/*   Updated: 2023/03/09 14:49:02 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	do_the_builtin(enum e_command command, char *args, int fd, t_info *info)
{
	if (command == pwd)
		ft_pwd(fd);
	else if (command == echo)
		ft_echo(args, fd);
	else if (command == exiter)
		ft_exit(args);
	else if (command == env)
		ft_env(info->env_cpy, fd);
	else if (command == unset)
		ft_unset(args, info);
	else if (command == cd)
		ft_cd(args);
	else if (command == exporter)
		ft_export(args, info);
	return (1);
}
