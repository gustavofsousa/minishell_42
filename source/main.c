/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:43:47 by gusousa           #+#    #+#             */
/*   Updated: 2023/02/27 16:31:05 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	finish_program(t_info *info, t_cell **list_cells)
{
	free(info->prompt);
	list_clear_cells(list_cells);
	exit (0);
}

void	reset(t_cell **list_cells)
{
//	if (info->prompt)
//		free(info.prompt);
	if (*list_cells)
		list_clear_cells(list_cells);
}

void	init(t_info *info, t_cell **list_cells)
{
	info->qtd_sent = 0;
	*list_cells = NULL;	
	//memset(info) // Ver se pode no pdf.
}

void	print_all_list(t_cell *list)
{
	printf("\n");
	while (list)
	{
		printf("-----------\n");
		if (list->token == 144)
			printf("Command&Word->\t%s\n", list->content);
		else if (list->token == 22)
			printf("redirect->\t%s\n", list->content);
		else if (list->token == 89)
			printf("Pipe->\t\t%s\n", list->content);
		list = list->next;
	}
}

void	print_sentence(t_list_sent *sent)
{
	printf("\n");
	while (sent)
	{
		printf("------sentence-----\n");
		printf("Command->\t%s\n", sent->content.command);
		printf("Arguments->\t%s\n", sent->content.args);
		sent = sent->next;
	}
}

int	main(int argc, char **argv)
{
	t_info	info;
	t_cell	*list_cells;
	t_list_sent	*sentence;

	(void)argc;
	(void)argv;
	init(&info, &list_cells);
	set_signal_handler();
	while (42)
	{
		//reset(&list_cells);
		info.prompt = readline("🦞our_minishell> ");
		add_history(info.prompt);
		check_eof(&info);
		divide_prompt(&info, &list_cells);
		categorize_elements(&list_cells);
		//expand_variable(&list_cells);
		handle_quotes(&list_cells);
		
		print_all_list(list_cells);

		sentence = create_sentence(list_cells, &info);
		//print_sentence(sentence);
		//golfer(t_sentence, &info);
	}
	//finish_program(&info, &list_cells);
	return (0);
}
//Para env:
// Remover o oldpwd
// Setar o sh-lvl para 1.
