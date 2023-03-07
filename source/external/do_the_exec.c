/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_the_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:58:48 by gusousa           #+#    #+#             */
/*   Updated: 2023/03/07 19:01:51 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	do_the_execve(t_info *info, t_list_sent *sent, char *args_out, int n_com)
{
	char	*command;
	char	**mtx_path;
	char	*right_path;
	char	*my_args;
	char	**right_args;
	int		success;
	int		nbr_child;

	command = get_command(n_com);
	mtx_path = get_path(info->env_cpy);
	right_path = get_rigt_path(mtx_path, command);
	my_args = ft_strjoin(command, " ");
	my_args = ft_strjoin_free(my_args, args_out);
	right_args = ft_split(my_args, ' ');

	if (info->qtd_sent > 0)
	{
		dup2(sent->content.input, 0);
		dup2(sent->content.output, 1);
	}
	else
		nbr_child = fork();
	if (nbr_child == 0)
	{
		//close_fdes();
		success = execve(right_path, right_args, info->env_cpy);
	}
	free(command);
	while (mtx_path)
		free((*mtx_path)++);
	free(mtx_path);
	free(right_path);
	free(my_args);
	while (right_args)
		free((*right_args)++);
	free(right_args);
	return (success);
}
