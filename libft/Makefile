NAME = libft.a

##################	Compiler	##################
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
MAKEFLAGS	=	--silent
RM = rm -rf

###	Directories	####
OBJDIR	:=	obj/

##################	Sources & OBJ	##################
SRC =	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c		\
		ft_strlen.c ft_strlcpy.c ft_strlcat.c ft_strchr.c ft_strrchr.c			\
		ft_strnstr.c ft_strncmp.c ft_striteri.c									\
		ft_strjoin.c ft_strtrim.c ft_split.c ft_strmapi.c ft_strdup.c			\
		ft_memset.c ft_memcpy.c ft_memmove.c ft_memchr.c ft_memcmp.c 			\
		ft_atoi.c ft_itoa.c ft_bzero.c											\
		ft_toupper.c ft_tolower.c ft_calloc.c ft_substr.c 						\
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c 			\
		ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c					\
		ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c

OBJ = $(addprefix $(OBJDIR), $(SRC:.c=.o))

################## ft_printf		##################

##################	Get_next_line	##################

##################	Commands	##################

all: $(OBJDIR) $(NAME)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(NAME): $(OBJ)
	ar -rcs $(NAME) $(OBJ)
	printf "\nLibft is ready\n"

$(OBJDIR)%.o : $(SRCDIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@
	printf "*"

clean:
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
