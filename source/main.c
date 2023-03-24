/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:43:47 by gusousa           #+#    #+#             */
/*   Updated: 2023/03/24 00:44:20 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	minishell(t_info *info, t_cell **list_cells, t_list_sent **sentence)
{
	info->prompt = readline("🦞our_minishell> ");
	check_eof(info);
	if (info->prompt && (*info).prompt)
	{
		add_history(info->prompt);
		if (divide_prompt(info, list_cells) == -1)
			return (0);
		categorize_elements(list_cells);
		expand_variable(list_cells, *info);
		handle_quotes(list_cells);
		*sentence = create_sentence(*list_cells, info);
		if (g_status != 130)
		{
			if (golfer(sentence, info) == -1)
				return (-1);
		}
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_info		info;
	t_cell		*list_cells;
	t_list_sent	*sentence;

	(void)argc;
	(void)argv;
	point_to_null(&info, &list_cells, &sentence);
	set_signal_handler();
	info.env_cpy = ft_cpy_env(envp);
	ft_unset("OLDPWD", &info);
	while (42)
	{
		reset(&info, &list_cells, sentence);
		if (minishell(&info, &list_cells, &sentence) == -1)
			break ;
		g_status = 0;
	}
	printf("Filho morreu\n");
	finish_program(&info, &list_cells, sentence);
	return (0);
}
