/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:43:47 by gusousa           #+#    #+#             */
/*   Updated: 2023/02/28 15:10:25 by parnaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	point_to_null(t_info *info, t_cell **list_cells, t_list_sent **sentence)
{
	info->prompt = NULL;
	info->env_cpy = NULL;
	info->qtd_sent = 0;
	*list_cells = NULL;	
	*sentence = NULL;
}

void	reset(t_info *info, t_cell **list_cells, t_list_sent **sentence)
{
	int	i;

	free(info->prompt);
	i = -1;
	if (info->env_cpy)
	{
		while (info->env_cpy[++i])
			free(info->env_cpy[i]);
		free(info->env_cpy);
	}
	list_clear_cells(list_cells);
	ft_lstclear_sent(sentence);
	point_to_null(info, list_cells, sentence);
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
		if(sent->content.args)
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
	point_to_null(&info, &list_cells, &sentence);
	set_signal_handler();
	while (42)
	{
		reset(&info, &list_cells, &sentence);
		info.prompt = readline("🦞our_minishell> ");
		add_history(info.prompt);
		check_eof(&info);
		divide_prompt(&info, &list_cells);
		categorize_elements(&list_cells);
		//expand_variable(&list_cells);
		handle_quotes(&list_cells);
		
		print_all_list(list_cells);

		sentence = create_sentence(list_cells, &info);
		printf("Rato\n");
		//print_sentence(sentence);
		//golfer(t_sentence, &info);
	}
	reset(&info, &list_cells, &sentence);
	exit(0);
	return (0);
}
//Para env:
// Remover o oldpwd
// Setar o sh-lvl para 1.
