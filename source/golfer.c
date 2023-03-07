/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   golfer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:58:48 by gusousa           #+#    #+#             */
/*   Updated: 2023/03/07 14:10:06 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	do_the_execve(char	**args_mtx, char **envp, char *command)
{
	char **path;
	char *str_path;
	int i;
	int ret;
	int acces;

	i = 0;
	ret = -1;
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
	printf("%s\n", str_path);
	path = ft_split(str_path, ':');
	i = 0;
	acces = access("/bin/ls", X_OK);
	printf("%s\n", ft_strjoin(path[0], command));
	if (fork() == 0)
		ret = execv("/bin/ls", args_mtx);
	//path = acces();
	// Criar um fork. O execve mata o processo.
	//ret = execve(path, ft_split(sent->content.args), info->env_cpy);
	//return (ret);
	//free(args_mtx);
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

int	create_forks(t_list_sent **senti, int qtd_pipes)
{
	int			i;
	int			n_sent;
	int			nbr_child;
	int			fildes[2];
	int			success;
	t_list_sent	*sent;

	sent = *senti;
	n_sent = -1;
	i = -1;
	while (++i < qtd_pipes)
	{
		success = pipe(fildes);//Primeiro le, segundo escreve.
		if (success == 0)
		{
				sent->content.output = fildes[1];
				sent = sent->next;
				if (sent == NULL)
					break;
				sent->content.input = fildes[0];
		}
	}
	nbr_child = 0;
	while (n_sent--)
	{
		nbr_child = fork();
	}
	return (nbr_child);
}

int	count_sentence(t_list_sent *sentence)
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

void	golfer(t_list_sent *sent, t_info *info)
{
	int	qtd_pipe;

	// Multipiping
	qtd_pipe = count_sentence(sent) - 1;
	if (qtd_pipe > 0)
		create_forks(&sent, qtd_pipe);

	if (sent->content.command != no_builtin)
		do_the_builtin(sent->content.command, sent->content.args,
				sent->content.output, info);
	else
	{
		do_the_execve(ft_split(sent->content.args, ' '), info->env_cpy, "/ls");
	}
}
