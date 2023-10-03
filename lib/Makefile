NAME	=	../lib.a

CC	=	cc

CFLAGS	=	-Wall -Wextra -Werror

AR	=	ar -rcs

RM	=	rm -rf

FILES	=	ft_strcmp ft_strlen ft_putendl_fd ft_putchar_fd ft_strchr ft_strdup ft_putstr_fd\
ft_substr ft_split ft_strjoin ft_free_arr

SRC	=	$(addsuffix .c, $(FILES))

OBJ	=	$(addsuffix .o, $(FILES))

all:	$(NAME)

%.o : %.c
		$(CC) -c $(CFLAGS) $< -o $@

$(OBJ) : *.%.o: *.%.c

$(NAME): $(OBJ)
		${AR} $(NAME) $(OBJ)

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY: all	clean fclean re
