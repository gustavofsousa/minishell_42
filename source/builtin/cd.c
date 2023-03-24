/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parnaldo <parnaldo@student.42.rio >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 21:44:56 by parnaldo          #+#    #+#             */
/*   Updated: 2023/03/24 09:05:13 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	do_the_change(char *path, t_info *info)
{
	int	status;
	char	*str;

	str = strdup("OLDPWD");
	str = ft_strjoin_free(str, "=");
	str = ft_strjoin_free(str, getcwd(NULL, 0));
	ft_export(str, info);
	status = chdir(path);
	free(str);
	return (status);
}

int	count_args(char *str)
{
	int		len;
	int		i;
	char	**mtx_str;

	len = 0;
	if (str == NULL)
		return (0);
	mtx_str = ft_split(str, ' ');
	i = -1;
	while (mtx_str[++i])
		len++;
	i = -1;
	while (mtx_str[++i])
		free(mtx_str[i]);
	free(mtx_str);
	return (len);
}

void	ft_cd(char *path, t_info *info)
{
	int	status;

	if (count_args(path) > 1)
	{
		ft_putstr_fd("cd: too many args\n", 2);
	}
	else
	{
		if (path == NULL)
			status = chdir(getenv("HOME"));
		else
			status = do_the_change(path, info);
		if (status == -1)
		{
			if (errno == 14)
				ft_putendl_fd("No such file or directory", 2);
			else
				perror("our_minishell: cd");

			g_status = 1;
			return ;
		}
	}
	g_status = 0;
}
// Usar perror() para esses e outros?
