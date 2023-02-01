/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:45:17 by gusousa           #+#    #+#             */
/*   Updated: 2023/02/01 15:45:36 by parnaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/ioctl.h>
# include "../libft/libft.h"

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

//Signal
void	check_eof(t_info *info);
void	init_sig(void);

#endif
