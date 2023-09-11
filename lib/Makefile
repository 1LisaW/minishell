NAME	=	../lib.a

CC	=	cc

CFLAGS	=	-Wall -Wextra -Werror

AR	=	ar -rcs

RM	=	rm -rf

FILES	=	ft_strcmp ft_strlen

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
