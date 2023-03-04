/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parnaldo <parnaldo@student.42.rio >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:45:17 by gusousa           #+#    #+#             */
/*   Updated: 2023/03/04 17:45:13 by gusousa          ###   ########.fr       */
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
# include <fcntl.h>//open().

enum e_token
{
	word = 144,
	redirect = 22,
	piper = 89
};

enum e_command
{
	pwd,
	echo,
	exiter,
	env,
	unset,
	exporter,
	cd,
	no_builtin
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
	int		qtd_sent;
	char	**env_cpy;
	int		*fd_heredoc;
}	t_info;

typedef struct s_sentence
{
	int					input;
	enum e_command		command;
	char				*args;// Tem que ser ** por causa do execv.
	int					output;
}	t_sentence;

typedef struct s_list_sent
{
	t_sentence			content;
	struct s_list_sent	*next;
}	t_list_sent;

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
void	golfer(t_list_sent *sent, t_info *info);

char	*ft_strjoin_free(char *s1, char *s2);
char	*ft_strjoin_char(char *s1, char c);

// Builtin
void		ft_pwd();
void		ft_echo(char *str, int fd);
void		ft_exit(char *str);
int			ft_env(char	**envsi, int fd);
int			ft_unset(char *arg, struct s_info *info);
char		**ft_cpy_env(char	**envs);
int			ft_export(char *arg, struct s_info *info);
void		ft_cd(char *path);

// List_sentence
void		ft_lstclear_sent(t_list_sent **lst);
void		ft_lstadd_back_sent(t_list_sent **lst, t_list_sent *new_node);
t_list_sent	*ft_lstnew_sent(t_sentence content);

//create_sentence.c
t_list_sent	*create_sentence(t_cell *list_in, t_info *info);
void		open_redirect(t_cell *list_in, t_sentence *sent, t_info *info);

#endif
