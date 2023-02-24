/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parnaldo <parnaldo@student.42.rio >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:45:17 by gusousa           #+#    #+#             */
/*   Updated: 2023/02/24 19:15:28 by gusousa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h> //printf
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <stdlib.h> //free
# include <unistd.h>//getcwd(); fork().
# include <stdlib.h>//exit. free.

enum e_token
{
	word = 144,
	redirect = 22,
	piper = 89
};

typedef struct s_cell
{
	char			*content;
	enum e_token	token;
	int				space;
	struct s_cell	*next;
}	t_cell;

typedef struct s_info
{
	char	*prompt;
	char	**sentence;
	int		qtd_sent;
	char	**env_cpy;
}	t_info;

typedef struct s_sentence
{
	int					input;
	char				*command;
	char				*args;// Tem que ser ** por causa do exeqv.
	int					output;
	struct s_sentence	*next;
}	t_sentence;

//Parser
void	divide_prompt(t_info *info, t_cell **list_cells);
void	categorize_elements(t_cell **list);
void	handle_quotes(t_cell **list_cells);

void	list_clear_cells(t_cell **list);
void	create_new_cell(t_cell **list_cells, char *str, int spce);

//Signal
void	check_eof(t_info *info);
void	set_signal_handler(void);

// main
void	expand_variable(t_cell **list_cell, t_info info);
void	golfer(t_sentence *sent, t_info *info);

char	*ft_strjoin_free(char *s1, char *s2);
char	*ft_strjoin_char(char *s1, char c);

// Builtin
void	ft_pwd();
void	ft_echo(char *str);
void	ft_exit(char *str);
int		ft_env(char	**envs);
int		ft_unset(char *arg, struct s_info *info);
char	**ft_cpy_env(char	**envs);
int		ft_export(char *arg, struct s_info *info);
void	ft_cd(char *path);

#endif
