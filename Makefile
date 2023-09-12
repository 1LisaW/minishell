NAME	=	minishell

LIB	= lib.a

CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror

RM		=	rm -rf

FILES	=	mini_shell processes signals

PARSER_FILES	=	parser

LEXER_FILES	=	lexer

SRC_DIR		= src

LEXER_DIR	= lexer

PARSER_DIR	= parser

OBJ_DIR	=	build

SRC	=	$(addsuffix .c, $(FILES))

LEXER_SRC	=	$(addprefix $(LEXER_DIR)/, $(addsuffix .c, $(LEXER_FILES)))

PARSER_SRC	=	$(addprefix $(PARSER_DIR)/, $(addsuffix .c, $(PARSER_FILES)))

SRCS	= $(addprefix $(SRC_DIR)/, $(SRC))

LEXER_SRCS	=	$(addprefix $(SRC_DIR)/, $(LEXER_SRC))

PARSER_SRCS	=	$(addprefix $(SRC_DIR)/, $(PARSER_SRC))

LEXER_OBJS	=	$(addsuffix .o, $(LEXER_FILES))

PARSER_OBJS	=	$(addsuffix .o, $(PARSER_FILES))

OBJS	=	$(addsuffix .o, $(FILES))

ALL_OBJS = $(OBJS) $(addprefix $(LEXER_DIR)/, $(LEXER_OBJS)) $(addprefix $(PARSER_DIR)/, $(PARSER_OBJS))

%.o : %.c
		$(CC) -c $(CFLAGS) $< -o $@


all:	$(NAME)

$(addprefix $(OBJ_DIR)/, $(OBJS)): $(addprefix $(OBJ_DIR)/$(LEXER_DIR)/, $(LEXER_OBJS))  $(addprefix $(OBJ_DIR)/$(PARSER_DIR)/, $(PARSER_OBJS))
		@mkdir -p $(OBJ_DIR)
		$(CC) -c $(CFLAGS) $(SRCS)
		mv $(OBJS) $(OBJ_DIR)/

$(addprefix $(OBJ_DIR)/$(LEXER_DIR)/, $(LEXER_OBJS)):
		@mkdir -p $(OBJ_DIR)/$(LEXER_DIR)
		$(CC) -c $(CFLAGS) $(LEXER_SRCS)
		mv $(LEXER_OBJS) $(OBJ_DIR)/$(LEXER_DIR)/


$(addprefix $(OBJ_DIR)/$(PARSER_DIR)/, $(PARSER_OBJS)):
		@mkdir -p $(OBJ_DIR)/$(PARSER_DIR)
		$(CC) -c $(CFLAGS) $(PARSER_SRCS)
		mv $(PARSER_OBJS) $(OBJ_DIR)/$(PARSER_DIR)/

$(LIB):
	cd lib && $(MAKE) all

$(NAME):	$(addprefix $(OBJ_DIR)/, $(ALL_OBJS)) $(LIB)
		$(CC) $(addprefix $(OBJ_DIR)/, $(ALL_OBJS))  -I include $(LIB) -lreadline -o $(NAME)

clean:
	$(RM) $(addprefix $(OBJ_DIR)/, $(ALL_OBJS)) $(OBJ_DIR)
	cd lib && $(MAKE) clean

fclean:	clean
	$(RM) $(NAME)
	cd lib && $(MAKE) fclean

re:	fclean all

.PHONY: all	clean fclean re
