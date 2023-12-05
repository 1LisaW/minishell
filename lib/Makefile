NAME	=	../lib.a

CC	=	cc

CFLAGS	=	-Wall -Wextra -Werror -g

AR	=	ar -rcs

RM	=	rm -rf

FILES	=	ft_strcmp ft_strlen ft_putendl_fd ft_putchar_fd ft_strchr \
ft_strdup ft_putstr_fd \
ft_substr ft_split ft_strjoin ft_free_arr ft_strcopy ft_strncmp ft_atol\
ft_strlcpy ft_isalpha ft_isalnum\
ft_issign ft_isspace ft_isdigit\
ft_itoa

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
