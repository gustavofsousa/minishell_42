/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parnaldo <parnaldo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 13:51:14 by parnaldo          #+#    #+#             */
/*   Updated: 2023/03/07 19:32:52 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_command(int way)
{
	if (way == 0)
		return (ft_strdup("pwd"));
	else if (way == 1)
		return (ft_strdup("echo"));
	else if (way == 2)
		return (ft_strdup("exit"));
	else if (way == 3)
		return (ft_strdup("env"));
	else if (way == 4)
		return (ft_strdup("unset"));
	else if (way == 5)
		return (ft_strdup("export"));
	else if (way == 6)
		return (ft_strdup("cd"));
	return (NULL);
}

char **get_path(char **envp)
{
	char *path;
	char **path_mtx;
	
	path = NULL;
	path_mtx = NULL;
	while (envp)
	{
		if (!ft_strncmp("PATH", *envp, 4))
		{
			path = ft_strdup(*(envp + 5));
			break ;
		}
		envp++;
	}
	path_mtx = ft_split(path, ':');
	free(path);
	return (path_mtx);
}

char *get_right_path(char **mtx_path, char *command)
{
	int	i;
	int access_return;
	char *path_command;

	path_command = NULL;
	i = 0;
	while (mtx_path[i] == NULL)
	{
		path_command = ft_strjoin(mtx_path[i], "/");
		path_command = ft_strjoin_free(path_command, command);
		access_return = access(path_command, F_OK);
		if (access_return == 0)
			break;
		free(path_command);
		path_command = NULL;
		i++;
	}
	return (path_command);
}

int	do_the_execve(t_info *info, t_list_sent *sent, char *args_out, int n_com)
{
	char	*command;
	char	**mtx_path;
	char	*right_path;
	char	*my_args;
	char	**right_args;
	int		success;
	int		nbr_child;

	nbr_child = 2;
	success = -1;
	command = get_command(n_com);
	mtx_path = get_path(info->env_cpy);
	right_path = get_right_path(mtx_path, command);
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
	/*
	free(command);
	while (mtx_path)
		free((*mtx_path)++);
	free(mtx_path);
	free(right_path);
	free(my_args);
	while (right_args)
		free((*right_args)++);
	free(right_args);
	*/
	return (success);
}
