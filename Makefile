# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: parnaldo <parnaldo@student.42.rio >        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/25 13:13:20 by gusousa           #+#    #+#              #
#    Updated: 2023/03/05 18:26:13 by gusousa          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	minishell
##MAKEFLAGS	:= --silent

####	Compilers & flags	####
CC		:=	cc
CFLAGS	:=	-Wextra -Wall -Werror -g -I ~/.brew/opt/readline/include

####	linkers		####
LINK		:=	-lreadline -L ~/.brew/opt/readline/lib

####	Directories	####
SRCDIR	:=	source/
OBJDIR	:=	obj/
INCDIR	:=	include/
LIBDIR	:=	libft/

####	Sources & objects	####

MAIN		:=	main.c	signal.c	golfer.c	expand_variables.c	ft_strjoin_free.c \
				create_sentence.c	list_sentence.c	redirect.c
PARSER		:=	parser.c list_cells.c token.c	handle_quotes.c
BUILTIN		:=	pwd.c echo.c exit.c env.c unset.c export.c cd.c

SRC		:=	$(MAIN)				\
			$(addprefix parser/, $(PARSER))			\
			$(addprefix builtin/, $(BUILTIN))	

OBJ		:=	$(addprefix $(OBJDIR), $(SRC:.c=.o))

####	Libft		####
LIBLIB		:=	$(LIBDIR)/libft.a

LISTDIR 	:=	builtin parser

#$(shell echo '$@ <- Nome da regra.')
#$(shell echo '$< <- Nome da primeira dependência.')
#$(shell echo '$^ <- Lista de dependências.')
#$(shell echo '$? <- Lista de dependências mais recentes que a regra.')
#$(shell echo '$* <- Nome do arquivo sem sufixo.')

# Colors
BLACK	=	\033[0;30m
BLUE	=	\033[0;34m
CYAN	=	\033[0;36m
GREEN	=	\033[0;32m
MAGENTA	=	\033[1;35m
ORANGE	=	\033[1;38;5;214m
RED		=	\033[0;31m
RESET	=	\033[0m
WHITE	=	\033[0;37m
YELLOW	=	\033[0;33m

######	Commands	######

all:	$(OBJDIR) $(LIBLIB) $(NAME)

$(OBJDIR):
	@mkdir -p $(OBJDIR)
	@mkdir -p $(addprefix $(OBJDIR), $(LISTDIR))
#	@$(foreach dir, $(LISTDIR), mkdir -p $(OBJDIR)/$(dir))

$(OBJDIR)%.o : $(SRCDIR)%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "objects created 😉 ->$(MAGENTA) $@$(WHITE)"

$(NAME): $(OBJ)
	@$(CC) $(OBJ) $(LIBLIB) $(LINK) -o $@
	@echo "Awesome! just execute it now 🤪"

$(LIBLIB):
	@make -C $(LIBDIR) all
	@echo "libf compiled 🙃"

clean:
	@rm -rf $(OBJDIR)
	@make -C $(LIBDIR) clean
	@echo Everything cleaned out🗑

fclean:	clean
	@rm -rf $(NAME)
	@make -C $(LIBDIR) fclean

re: fclean all

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes --track-fds=yes ./minishell

.PHONY: re, fclean, clean, all
