/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parnaldo <parnaldo@student.42.rio >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:45:17 by gusousa           #+#    #+#             */
/*   Updated: 2023/03/27 17:47:07 by gusousa          ###   ########.fr       */
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
# include <sys/types.h>//waitpid.
# include <sys/wait.h>//waitpid.
# include <errno.h>

// to install readline please execute:
// sudo apt-get install libreadline8 && sudo apt-get install libreadline-dev

extern int			g_status;

enum e_token
{
	word = 144,
	redirect = 22,
	piper = 89
};

enum e_command
{
	start,
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

typedef struct s_sentence
{
	int					input;
	enum e_command		command;
	char				*args;
	int					output;
}	t_sentence;

typedef struct s_list_sent
{
	t_sentence			content;
	struct s_list_sent	*next;
}	t_list_sent;

typedef struct s_info
{
	char		*prompt;
	int			qtd_sent;
	char		**env_cpy;
	int			*nbr_pids;
	int			stop;
	t_list_sent	*head;
}	t_info;

//Parser
int			divide_prompt(t_info *info, t_cell **list_cells);
int			categorize_elements(t_cell **list);
int			handle_quotes(t_cell **list_cells);
void		delete_cell(t_cell **init_cell, t_cell **list);
void		list_clear_cells(t_cell **list);
void		create_new_cell(t_cell **list_cells, char *str, int spce);

//Signal
void		check_eof(t_info *info);
void		set_signal_handler(void);

// main
int			golfer(t_list_sent **sent, t_info *info);
void		config_fd_system(t_list_sent *sent, t_info *info);

char		*ft_strjoin_free(char *s1, char *s2);
char		*ft_strjoin_char(char *s1, char c);

// Builtin
void		ft_pwd(int fd);
void		ft_echo(char *str, int fd);
void		ft_exit(char *str, int fd);
int			ft_env(char	**envsi, int fd);
int			ft_unset(char *arg, struct s_info *info);
char		**ft_cpy_env(char	**envs);
int			ft_export(char *arg, struct s_info *info);
void		ft_cd(char *path, t_info *info);
void		print_err_export(char *str);

// pipes
void		open_pipes(t_list_sent **sent, t_info *info);
void		config_fd_system(t_list_sent *sent, t_info *info);
void		wait_children_die(t_info *info);

// parser
void		ft_lstclear_sent(t_list_sent **lst);
void		ft_lstadd_back_sent(t_list_sent **lst, t_list_sent *new_node);
t_list_sent	*ft_lstnew_sent(t_sentence content);
void		expand_variable(t_cell **list_cell, t_info info);
int			calc_len_content(t_cell **list, t_info info, int index);
int			len_word(char *str);
char		**ft_split_mod(char const *s, char c, int *fq);
char		*ft_strdup_char(char c);
void		dup_or_join_char(t_cell **list, char c);
void		dup_or_join_string(t_cell **list, char *new_value);

//create_sentence.c
t_list_sent	*create_sentence(t_cell *list_in, t_info *info);
int			open_redirect(t_cell *list_in, t_sentence *sent, t_info *info);
int			do_heredoc(t_cell *list_in, t_sentence *sent, t_info *info);

//extern
char		*prepare_path(t_info *info, t_list_sent *sent);
char		*ft_substitute(char *str);

//Finish program and things.
void		close_fdes(t_info *info);
void		freeing_local(char *right_path, char **right_args);
void		finish_program(t_info *info, t_cell **list_cells,
				t_list_sent **sentence);
void		point_to_null(t_info *info, t_cell **list_cells,
				t_list_sent **sentence);
void		reset(t_info *info, t_cell **list_cells, t_list_sent **sentence);

// Expand Variable
char		*ft_cpychar_noprint(char *str);
int			cpy_str(t_cell **list, char *str, int i);
int			is_variable(char *str, char *env, int len_str, int i);
int			deal_with_dollar(t_cell **list, t_info info, char *str, int i);
int			get_value_env(t_info info, t_cell **list, char *str, int i);

// Env
int			ft_strlen_env(char *s);
int			is_equal_env(char *arg, char **env);

#endif
