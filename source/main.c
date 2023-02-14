/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:43:47 by gusousa           #+#    #+#             */
/*   Updated: 2023/02/14 15:08:52 by gusousa          ###   ########.fr       */
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

void	print_all_list(t_cell *list)
{
	int	i;

	i = 0;
	printf("\n");
	while (list)
	{
		printf("-----------\n");
		printf("Cell nº:\t%d\n", ++i);
		printf("Content:\t%s\n", list->content);
		printf("Token:\t\t%u\n", list->token);
		list = list->next;
	}
}

int	main(int argc, char **argv)
{
	t_info	info;
	t_cell	*list_cells;

	(void)argc;
	(void)argv;
	init(&info, &list_cells);
	set_signal_handler();
	while (42)
	{
		reset(&list_cells);
		info.prompt = readline("🦞our_minishell> ");
		add_history(info.prompt);
		check_eof(&info);
		divide_prompt(&info, &list_cells);
		categorize_elements(&list_cells);

		print_all_list(list_cells);

		expand_variable(&list_cells);
		create_sentence(t_sentence); //faz aqui o redirect
		golfer(t_sentence);

		//info.sentence = &info.prompt;
		//Se for exit, dar break.
	}
	finish_program(&info, &list_cells);
	return (0);
}

/*
executioer

{
	pipes();
	choose_commands();
}
*/

//Para env:
// Remover o oldpwd
// Setar o sh-lvl para 1.
