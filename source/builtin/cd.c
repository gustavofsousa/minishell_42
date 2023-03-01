/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parnaldo <parnaldo@student.42.rio >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 21:44:56 by parnaldo          #+#    #+#             */
/*   Updated: 2023/03/01 11:02:27 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	free(mtx_str[i]);
	return (len);
}

// Atualizar $OLDPWD?
void	ft_cd(char *path)
{
	int	status;

	if (count_args(path) > 1)
	{
		ft_putstr_fd("cd: too many args\n", 2);
		//return (1);//Which number?
	}
	else
	{
		if (path == NULL)
			status = chdir(getenv("HOME"));
		else
			status = chdir(path);
		if (status == -1)
		{
			ft_putstr_fd("cd failed. path not found(?)", 2);
			//return (1);//Retorna qual numero?
		}
	}
}
// Usar perror() para esses e outros?
