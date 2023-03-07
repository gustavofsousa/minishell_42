/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parnaldo <parnaldo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 13:51:14 by parnaldo          #+#    #+#             */
/*   Updated: 2023/03/07 18:36:29 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			path = ft_strdup(&(envp + 5));
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
	acess_return = -1;
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
