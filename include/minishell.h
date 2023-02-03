/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:45:17 by gusousa           #+#    #+#             */
/*   Updated: 2023/02/03 20:13:21 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h> //printf
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include <stdlib.h> //free

typedef struct s_cell
{
	char			*content;
	int				token;
	int				id;
	struct s_cell	*next;
}	t_cell;

typedef struct s_info
{
	char	*prompt;
	char	**sentence;
	int		qtd_sentence;

}	t_info;

typedef struct s_commands
{
	char	*input;
	char	*command;
	char	*arguments;
	char	*output;
	char	*output;
}	t_command;

t_cell	*divide_prompt(t_info *info);
void	create_new_cell(t_cell **list_cells, char *str);

#endif
