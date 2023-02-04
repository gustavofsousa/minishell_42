# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/25 13:13:20 by gusousa           #+#    #+#              #
#    Updated: 2023/02/04 11:10:45 by gusousa          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	minishell
##MAKEFLAGS	:= --silent

####	Compilers & flags	####
CC		:=	cc
CFLAGS	:=	-Wextra -Wall -Werror -g

####	linkers		####
LINK		:=	-lreadline

####	Directories	####
SRCDIR	:=	source/
OBJDIR	:=	obj/
INCDIR	:=	include/
LIBDIR	:=		./libft

####	Sources & objects	####
SRC		:=	main.c			parser.c							\
			list_cells.c	token.c

OBJ		:=	$(addprefix $(OBJDIR), $(SRC:.c=.o))

####	Libft		####
LIBLIB		:=	$(LIBDIR)/libft.a

######	Commands	######

all:	$(OBJDIR) $(LIBLIB) $(NAME)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)%.o : $(SRCDIR)%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo objects created ;)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) $(LIBLIB) $(LINK) -o $@
	@echo Awesome! just execute it now

$(LIBLIB):
	@make -C $(LIBDIR) all
	@echo libf compiled :)

clean:
	@rm -rf $(OBJDIR)
	@make -C $(LIBDIR) clean
	@echo Everything cleaned out

fclean:	clean
	@rm -rf $(NAME)
	@make -C $(LIBDIR) fclean

re: fclean all

.PHONY: re, fclean, clean, all
