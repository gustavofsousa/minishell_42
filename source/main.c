/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:43:47 by gusousa           #+#    #+#             */
/*   Updated: 2023/02/01 15:20:10 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void	finish_program(t_info *info)
{
	int	i;

	i = -1;
	free(info->prompt);
	if (info->sentence)
	{
		while (++i < info->qtd_sentence)
			free(info->sentence);
		free(info->sentence);
	}
	exit (0);
}

void	count_sentence(t_info *info)
{
	int	i;

	i = -1;
	while (info->sentence[++i])
		info->qtd_sentence++;
}

void	init(t_info *info)
{
	info->qtd_sentence = 0;
}

int	main(int argc, char **argv)
{
	t_info	info;

	(void)argc;
	(void)argv;
	init(&info);
	while (42)
	{
		//reset()
		info.prompt = readline("nosso_minisheel> ");
		add_history(info.prompt);
		divide_prompt(&info);

		//info.sentence = ft_split(info.prompt, '|');
		//count_sentence(&info);
		//Se for exit, dar break.
	}

	finish_program(&info);
	return (0);
}
