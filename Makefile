# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gusousa <gusousa@student.42.rio>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/25 13:13:20 by gusousa           #+#    #+#              #
#    Updated: 2023/01/25 13:42:47 by gusousa          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	minishell
MAKEFLAGS	:= --silent

####	Compilers	####
CC		:=	cc
CFLAGS	:=	-Wextra -Wall -Werror -g

####	Directories	####
SRCDIR	:=	source/
OBJDIR	:=	obj/
INCDIR	:=	include/

####	Sources & objects	####
SRC		:=	main.c							\

OBJ		:=	$(addprefix $(OBJDIR), $(SRC:.c=.o))

####	Commands	####

all:	$(OBJDIR) $(NAME)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(NAME): 




clean:
	rm -rf $(OBJDIR)

fclean:	clean
	rm -rf $(NAME)

re: fclean all

.PHONY: re, fclean, clean, all
