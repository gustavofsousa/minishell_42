/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:43:47 by gusousa           #+#    #+#             */
/*   Updated: 2023/03/04 18:22:10 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	point_to_null(t_info *info, t_cell **list_cells, t_list_sent **sentence)
{
	info->prompt = NULL;
	//info->env_cpy = NULL;
	info->qtd_sent = 0;
	*list_cells = NULL;	
	*sentence = NULL;
	info->fd_heredoc = NULL;
}

void	reset(t_info *info, t_cell **list_cells, t_list_sent **sentence)
{
	int	i;

	free(info->prompt);
	i = -1;
	/*
	if (info->env_cpy)
	{
		while (info->env_cpy[++i])
			free(info->env_cpy[i]);
		free(info->env_cpy);
	}
	*/
	list_clear_cells(list_cells);
	ft_lstclear_sent(sentence);
	if (info->fd_heredoc)
		free(info->fd_heredoc);
	point_to_null(info, list_cells, sentence);
	//close fd's i opened.
}

void	finish_program(t_info *info, t_cell **list_cells, t_list_sent **sentence)
{
	reset(info, list_cells, sentence);
	exit (0);
}

void	print_all_list(t_cell *list)
{
	printf("\n");
	while (list)
	{
		if (list->token == 144)
			printf("Command&Word->\t%s\n", list->content);
		else if (list->token == 22)
			printf("redirect->\t%s\n", list->content);
		else if (list->token == 89)
			printf("Pipe->\t\t%s\n", list->content);
		list = list->next;
	}
	printf("\n");
}

void	print_sentence(t_list_sent *sent)
{
	printf("\n");
	while (sent)
	{
		printf("-----------sentence----------\n");
		printf("Input:%d\t", sent->content.input);
		printf("Command->%u\t", sent->content.command);
		printf("Arguments->%s\t", sent->content.args);
		printf("Output:%d\n", sent->content.output);
		sent = sent->next;
	}
	printf("\n");
}

int	main(int argc, char **argv, char **envp)
{
	t_info	info;
	t_cell	*list_cells;
	t_list_sent	*sentence;

	(void)argc;
	(void)argv;
	point_to_null(&info, &list_cells, &sentence);
	set_signal_handler();
	info.env_cpy = ft_cpy_env(envp);
	while (42)
	{
		reset(&info, &list_cells, &sentence);
		info.prompt = readline("🦞our_minishell> ");
		add_history(info.prompt);
		check_eof(&info);
		divide_prompt(&info, &list_cells);
		categorize_elements(&list_cells);
		//expand_variable(&list_cells);
		if (handle_quotes(&list_cells) == -1)
			finish_program(&info, &list_cells, &sentence);
		//print_all_list(list_cells);
		//sentence = create_sentence(list_cells, &info);
		print_sentence(sentence);
		golfer(sentence, &info);
	}
	reset(&info, &list_cells, &sentence);
	exit(0);
	return (0);
}
//Para env:
// Remover o oldpwd
// Setar o sh-lvl para 1.
