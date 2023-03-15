/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parnaldo <parnaldo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 13:51:14 by parnaldo          #+#    #+#             */
/*   Updated: 2023/03/15 16:39:29 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_command(char *str)
{
	int	i;

	i = 0;
	while (str[i] != ' ' && str[i] != '\0')
		i++;
	return (ft_substr(str, 0, i));
}

char	**get_path(char **envp)
{
	char	*path;
	char	**path_mtx;

	path = NULL;
	path_mtx = NULL;
	while (*envp)
	{
		if (!ft_strncmp("PATH", *envp, 4))
		{
			path = ft_strdup((*envp + 5));
			break ;
		}
		envp++;
	}
	path_mtx = ft_split(path, ':');
	free(path);
	return (path_mtx);
}

char	*get_right_path(char **mtx_path, char *command)
{
	int		i;
	int		access_return;
	char	*path_command;

	path_command = NULL;
	i = 0;
	while (mtx_path[i] != NULL)
	{
		path_command = ft_strjoin(mtx_path[i], "/");
		path_command = ft_strjoin_free(path_command, command);
		access_return = access(path_command, F_OK);
		if (access_return == 0)
			break ;
		free(path_command);
		path_command = NULL;
		i++;
	}
	return (path_command);
}

char	*prepare_path(t_info *info, t_list_sent *sent)
{
	char	**mtx_path;
	char	*right_path;
	char	*command;
	int		i;

	if (sent->content.args[0] == '/')
	{
		i = 0;
		while (sent->content.args[i] || sent->content.args[i] != ' ')
			i++;
		return (ft_substr(sent->content.args, 0, i));
	}
	mtx_path = get_path(info->env_cpy);
	command = get_command(sent->content.args);
	right_path = get_right_path(mtx_path, command);
	if (mtx_path)
	{
		i = -1;
		while (mtx_path[++i])
			free(mtx_path[i]);
		free(mtx_path);
	}
	return (free(command), right_path);
}

char	*ft_substitute(char *str)
{
	char	*tmp;

	if (str[0] == '/')
	{
		tmp = ft_strrchr(str, '/');
		tmp = ft_strdup(tmp + 1);
		free(str);
		return (tmp);
	}
	return (str);
}
