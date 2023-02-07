# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/25 13:13:20 by gusousa           #+#    #+#              #
#    Updated: 2023/02/07 14:09:44 by gusousa          ###   ########.fr        #
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

MAIN		:=	main.c
PARSER		:=	parser.c list_cells.c token.c
SIGNAL		:=	signal.c
BUILTIN		:=	pwd.c
#cd.c echo.c env.c exit.c export.c pwd.c unset.c

SRC		:=	$(MAIN)				\
			$(PARSER)			\
			$(SIGNAL)				\
			$(addprefix builtin/, $(BUILTIN))	

OBJ		:=	$(addprefix $(OBJDIR), $(SRC:.c=.o))

####	Libft		####
LIBLIB		:=	$(LIBDIR)/libft.a

LISTDIR = builtin parser

#$(shell echo '$@ <- Nome da regra.')
#$(shell echo '$< <- Nome da primeira dependência.')
#$(shell echo '$^ <- Lista de dependências.')
#$(shell echo '$? <- Lista de dependências mais recentes que a regra.')
#$(shell echo '$* <- Nome do arquivo sem sufixo.')

######	Commands	######

all:	$(OBJDIR) $(LIBLIB) $(NAME)

$(OBJDIR):
	@mkdir -p $(OBJDIR)/builtin
	##@$(foreach dir, $(LISTDIR), mkdir -p $(dir))

$(OBJDIR)%.o : $(SRCDIR)%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo objects created 😉

$(NAME): $(OBJ)
	@$(CC) $(OBJ) $(LIBLIB) $(LINK) -o $@
	@echo Awesome! just execute it now 🤪

$(LIBLIB):
	@make -C $(LIBDIR) all
	@echo libf compiled 🙃

clean:
	@rm -rf $(OBJDIR)
	@make -C $(LIBDIR) clean
	@echo Everything cleaned out🗑

fclean:	clean
	@rm -rf $(NAME)
	@make -C $(LIBDIR) fclean

re: fclean all

.PHONY: re, fclean, clean, all
