/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:45:17 by gusousa           #+#    #+#             */
/*   Updated: 2023/02/02 18:41:37 by gusousa          ###   ########.fr       */
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
	struct s_cell	*next;
}	t_cell;

typedef struct s_betpip
{
	char			*sentence;
	int				qtd_word;
	struct s_betpip	*next;
}	t_betpip;

typedef struct s_info
{
	char	*prompt;
	char	**sentence;
	int		qtd_sentence;




}	t_info;

void	divide_prompt(t_info *info);

#endif
