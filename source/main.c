/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:43:47 by gusousa           #+#    #+#             */
/*   Updated: 2023/02/04 11:11:21 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void	finish_program(t_info *info, t_cell **list_cells)
{
	int	i;

	i = -1;
	free(info->prompt);
	list_clear_cells(list_cells);
	exit (0);
}

void	reset(t_cell **list_cells)
{
	if (*list_cells)
		list_clear_cells(list_cells);
	
}

void	init(t_info *info, t_cell **list_cells)
{
	info->qtd_sentence = 0;
	*list_cells = NULL;	
}

int	main(int argc, char **argv)
{
	t_info	info;
	t_cell	*list_cells;

	(void)argc;
	(void)argv;
	init(&info, &list_cells);
	while (42)
	{
		reset(&list_cells);
		info.prompt = readline("our_minishell> ");
		add_history(info.prompt);
		list_cells = divide_prompt(&info);
		categorize_elements(&list_cells);

		//info.sentence = ft_split(info.prompt, '|');
		//count_sentence(&info);
		//Se for exit, dar break.
	}

	finish_program(&info, &list_cells);
	return (0);
}
