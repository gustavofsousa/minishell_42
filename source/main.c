/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:43:47 by gusousa           #+#    #+#             */
/*   Updated: 2023/02/01 10:45:40 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void	finish_program(t_info *info)
{
	free(info->prompt);
	exit (0);
}


int	main(int argc, char **argv)
{
	t_info	info;

	(void)argc;
	(void)argv;
	while (42)
	{
		//reset()
		info.prompt = readline("nosso_minisheel> ");
		add_history(info.prompt);
		printf("%s\n", info.prompt);
		//Se for exit, dar break.
	}

	finish_program(&info);
	return (0);
}
