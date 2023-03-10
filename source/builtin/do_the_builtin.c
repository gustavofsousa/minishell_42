/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_the_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:47:45 by gusousa           #+#    #+#             */
/*   Updated: 2023/03/10 10:36:46 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	do_the_builtin(t_list_sent *sent, t_info *info)
{
	
	config_fd_system(sent, info);
	if (sent->content.command == pwd)
		ft_pwd(sent->content.output);
	else if (sent->content.command == echo)
		ft_echo(sent->content.args, sent->content.output);
	else if (sent->content.command == exiter)
		ft_exit(sent->content.args);
	else if (sent->content.command == env)
		ft_env(info->env_cpy, sent->content.output);
	else if (sent->content.command == unset)
		ft_unset(sent->content.args, info);
	else if (sent->content.command == cd)
		ft_cd(sent->content.args);
	else if (sent->content.command == exporter)
		ft_export(sent->content.args, info);
	return (1);
}
