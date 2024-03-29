/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   golfer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:58:48 by gusousa           #+#    #+#             */
/*   Updated: 2023/03/27 17:34:27 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	set_error(void)
{
	g_status = 1;
	if (errno == 14)
	{
		ft_putendl_fd("command not found", 2);
		g_status = 127;
	}
	else
	{
		perror("error");
		g_status = 127;
	}
	return (-1);
}

int	do_the_execve(t_info *info, t_list_sent *sent, int i)
{
	char	*right_path;
	char	**right_args;

	right_path = prepare_path(info, sent);
	right_args = ft_split(sent->content.args, ' ');
	info->nbr_pids[i] = fork();
	if (info->nbr_pids[i] == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		config_fd_system(sent, info);
		execve(right_path, right_args, info->env_cpy);
		freeing_local(right_path, right_args);
		return (set_error());
	}
	freeing_local(right_path, right_args);
	return (0);
}

int	do_the_builtin(t_list_sent *sent, t_info *info, int i)
{
	if (info->qtd_sent > 1)
	{
		info->nbr_pids[i] = fork();
		if (info->nbr_pids[i] > 0)
			return (1);
	}
	if (sent->content.command == pwd)
		ft_pwd(sent->content.output);
	else if (sent->content.command == echo)
		ft_echo(sent->content.args, sent->content.output);
	else if (sent->content.command == exiter)
		ft_exit(sent->content.args, sent->content.output);
	else if (sent->content.command == env)
		ft_env(info->env_cpy, sent->content.output);
	else if (sent->content.command == unset)
		ft_unset(sent->content.args, info);
	else if (sent->content.command == cd)
		ft_cd(sent->content.args, info);
	else if (sent->content.command == exporter)
		ft_export(sent->content.args, info);
	if (info->qtd_sent > 1)
		return (-1);
	return (1);
}

int	golfer(t_list_sent **sent, t_info *info)
{
	int	i;

	i = 0;
	info->nbr_pids = ft_calloc(info->qtd_sent, sizeof(int));
	open_pipes(sent, info);
	while (*sent)
	{
		if ((*sent)->content.command != no_builtin)
		{
			if (do_the_builtin(*sent, info, i) == -1)
				return (-1);
		}
		else
		{
			if (do_the_execve(info, *sent, i) == -1)
				return (-1);
		}
		i++;
		*sent = (*sent)->next;
	}
	close_fdes(info);
	wait_children_die(info);
	*sent = info->head;
	return (0);
}
