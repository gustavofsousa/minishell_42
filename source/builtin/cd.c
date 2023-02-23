/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parnaldo <parnaldo@student.42.rio >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 21:44:56 by parnaldo          #+#    #+#             */
/*   Updated: 2023/02/23 16:59:56 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Atualizar $OLDPWD?
void	substitute_wave(char **path)
{
		if (ft_strchr(*path, '~'))
		(void)path;			
}

int	count_args(char *str)
{
	int		len;
	int		i;
	char	**mtx_str;

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

int ft_cd(char *path, t_info info)
{
	int	status;

	if (count_args(path) == 1)
	{
		substitute_wave(&path);
			status = chdir(path);
			if (status == -1)
			{
				ft_putstr_fd("cd failed. path not found(?)", 2);
				//perror("cd");
				//return (1);//Retorna qual numero?
			}
	}
	else
	{
			if (path == NULL)
			{
				// no directory provided
				ft_putstr_fd("cd: missing operand\n", 2);
				//return (1);//Which number?
			}

	}
	// if (~)
	// Tem que ir para home da env.

}
