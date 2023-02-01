# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/25 13:13:20 by gusousa           #+#    #+#              #
#    Updated: 2023/02/01 10:44:37 by gusousa          ###   ########.fr        #
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
SRC		:=	main.c							\

OBJ		:=	$(addprefix $(OBJDIR), $(SRC:.c=.o))

####	Libft		####
LIBLIB		:=	$(LIBDIR)/libft.a

######	Commands	######

all:	$(OBJDIR) $(LIBLIB) $(NAME)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)%.o : $(SRCDIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LINK) -o $@

$(LIBLIB):
	make -C $(LIBDIR) all

clean:
	rm -rf $(OBJDIR)

fclean:	clean
	rm -rf $(NAME)

re: fclean all

.PHONY: re, fclean, clean, all
