NAME	=	minishell

LIB	= lib.a

CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror -g

RM		=	rm -rf

FILES	=	mini_shell processes data_init signals env_vars

PARSER_FILES	=	syntax_parser parser_data parse_redirection build_parser_tree

LEXER_FILES	=	lexer lexer_data tokenizer

HELPERS_FILES = helpers modify_cmd modify_cmd_helpers modify_cmd_helpers2

EXEC_FILES	= executor execute_process redirect redir_utils heredoc_redir

BUILTINS_FILES = pwd cd echo

SRC_DIR		= src

LEXER_DIR	= lexer

PARSER_DIR	= syntax_parser

EXEC_DIR	= executor

HELPERS_DIR = helpers

BUILTINS_DIR = builtins

OBJ_DIR	=	build

SRC	=	$(addsuffix .c, $(FILES))

LEXER_SRC	=	$(addprefix $(LEXER_DIR)/, $(addsuffix .c, $(LEXER_FILES)))

PARSER_SRC	=	$(addprefix $(PARSER_DIR)/, $(addsuffix .c, $(PARSER_FILES)))

EXEC_SRC	=	$(addprefix $(EXEC_DIR)/, $(addsuffix .c, $(EXEC_FILES)))

HELPERS_SRC	=	$(addprefix $(HELPERS_DIR)/, $(addsuffix .c, $(HELPERS_FILES)))

BUILTINS_SRC	=	$(addprefix $(BUILTINS_DIR)/, $(addsuffix .c, $(BUILTINS_FILES)))

SRCS	= $(addprefix $(SRC_DIR)/, $(SRC))

LEXER_SRCS	=	$(addprefix $(SRC_DIR)/, $(LEXER_SRC))

PARSER_SRCS	=	$(addprefix $(SRC_DIR)/, $(PARSER_SRC))

EXEC_SRCS	=	$(addprefix $(SRC_DIR)/, $(EXEC_SRC))

HELPERS_SRCS	=	$(addprefix $(SRC_DIR)/, $(HELPERS_SRC))

BUILTINS_SRCS	=	$(addprefix $(SRC_DIR)/, $(BUILTINS_SRC))

LEXER_OBJS	=	$(addsuffix .o, $(LEXER_FILES))

PARSER_OBJS	=	$(addsuffix .o, $(PARSER_FILES))

HELPERS_OBJS	=	$(addsuffix .o, $(HELPERS_FILES))

BUILTINS_OBJS	=	$(addsuffix .o, $(BUILTINS_FILES))

EXEC_OBJS	=	$(addsuffix .o, $(EXEC_FILES))

OBJS	=	$(addsuffix .o, $(FILES))

ALL_OBJS = $(OBJS) $(addprefix $(LEXER_DIR)/, $(LEXER_OBJS)) $(addprefix $(PARSER_DIR)/, $(PARSER_OBJS)) \
           $(addprefix $(EXEC_DIR)/, $(EXEC_OBJS)) $(addprefix $(HELPERS_DIR)/, $(HELPERS_OBJS)) \
           $(addprefix $(BUILTINS_DIR)/, $(BUILTINS_OBJS))

%.o : %.c
		$(CC) -c $(CFLAGS) $< -o $@


all:	$(NAME)

$(addprefix $(OBJ_DIR)/, $(OBJS)): $(SRCS) \
									$(addprefix $(OBJ_DIR)/$(LEXER_DIR)/, $(LEXER_OBJS)) \
                                   $(addprefix $(OBJ_DIR)/$(PARSER_DIR)/, $(PARSER_OBJS)) \
                                   $(addprefix $(OBJ_DIR)/$(EXEC_DIR)/, $(EXEC_OBJS)) \
                                   $(addprefix $(OBJ_DIR)/$(HELPERS_DIR)/, $(HELPERS_OBJS)) \
                                   $(addprefix $(OBJ_DIR)/$(BUILTINS_DIR)/, $(BUILTINS_OBJS))
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

$(addprefix $(OBJ_DIR)/$(EXEC_DIR)/, $(EXEC_OBJS)): $(EXEC_SRCS)
		@mkdir -p $(OBJ_DIR)/$(EXEC_DIR)
		$(CC) -c $(CFLAGS) $(EXEC_SRCS)
		mv $(EXEC_OBJS) $(OBJ_DIR)/$(EXEC_DIR)/

$(addprefix $(OBJ_DIR)/$(HELPERS_DIR)/, $(HELPERS_OBJS)): $(HELPERS_SRCS)
		@mkdir -p $(OBJ_DIR)/$(HELPERS_DIR)
		$(CC) -c $(CFLAGS) $(HELPERS_SRCS)
		mv $(HELPERS_OBJS) $(OBJ_DIR)/$(HELPERS_DIR)/

$(addprefix $(OBJ_DIR)/$(BUILTINS_DIR)/, $(BUILTINS_OBJS)):
		@mkdir -p $(OBJ_DIR)/$(BUILTINS_DIR)
		$(CC) -c $(CFLAGS) $(BUILTINS_SRCS)
		mv $(BUILTINS_OBJS) $(OBJ_DIR)/$(BUILTINS_DIR)/

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
