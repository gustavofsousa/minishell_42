/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   golfer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:58:48 by gusousa           #+#    #+#             */
/*   Updated: 2023/03/04 18:39:33 by parnaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
void	create_forks(t_sentence *sent, int qtd_sent)
{
	int	nbr_child;

	nbr_child = 0;
	while (qtd_sent--)
	{
		//pipe();
		nbr_child = fork();
	}
}

int	count_sentence(t_sentence *sentence)
{
	int	len;

	len = 0;
	while (sentence)
	{
		len++;
		sentence = sentence->next;
	}
	return (len);
}
*/

int	do_the_execve(char	**args_mtx, char **envp)
{
	char **path;
	char *str_path;
	int i;

	i = 0;
	str_path = NULL;
	while (envp[i])
	{
		if(!ft_strncmp("PATH", envp[i], 4))
		{
			str_path = ft_strdup(envp[i]+5);
			break ;
		}
		i++;
	}
	path = ft_split(str_path, ':');
	//path = acces();
	// Criar um fork. O execve mata o processo.
	//ret = execve(path, ft_split(sent->content.args), info->env_cpy);
	//return (ret);
	//free(args_mtx);
	(void)args_mtx;
	(void)envp;
	return (1);
}

int	do_the_builtin(enum e_command command, char *args, int fd, t_info *info)
{
	if (command == pwd)
		ft_pwd(fd);
	else if (command == echo)
		ft_echo(args, fd);
	else if (command == exiter)
		ft_exit(args);
	else if (command == env)
		ft_env(info->env_cpy, fd);
	else if (command == unset)
		ft_unset(args, info);
	else if (command == cd)
		ft_cd(args);
	else if (command == exporter)
		ft_export(args, info);
	return (1);
}

void	golfer(t_list_sent *sent, t_info *info)
{
/*
	int	qtd_sent;

	// Multipiping
	qtd_sent = count_sentence(sent);
	if (qtd_sent > 1)
		create_forks(sent, qtd_sent);
*/

	if (sent->content.command != no_builtin)
		do_the_builtin(sent->content.command, sent->content.args,
				sent->content.output, info);
	else
	{
		do_the_execve(ft_split(sent->content.args, ' '), info->env_cpy);
	}
}
