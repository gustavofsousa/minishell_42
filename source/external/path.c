/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parnaldo <parnaldo@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 13:51:14 by parnaldo          #+#    #+#             */
/*   Updated: 2023/03/06 15:20:33 by parnaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char **get_path(char **envp)
{
	int i;
	char *path;
	char **path_mtx;
	
	i = 0;
	path = NULL;
	path_mtx = NULL;
	while (envp[i])
	{
		if(!ft_strncmp("PATH", envp[i], 4))
		{
			path = ft_strdup(envp[i]+5);
			break ;
		}
		i++;
	}
	path_mtx = ft_split(path, ':');
	return (path_mtx);
}

char *check_access_path(char **path, char *command)
{
	int	i;
	int access_return;
	char *path_command;

	acess_return = -1;
	i = 0;
	while (acess_return != -1 || path[i] == NULL)
	{
		
		acess_return = access(path_command, F_OK);
	}
}
