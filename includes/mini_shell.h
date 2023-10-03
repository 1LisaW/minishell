/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:58:51 by tklimova          #+#    #+#             */
/*   Updated: 2023/10/04 00:30:48 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include "../lib/lib.h"
# include <unistd.h>
# include <sys/types.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdlib.h>

typedef enum e_lexer_type {
	word,
	operator,
	redir_notation
}	t_lexer_type;

typedef enum e_sparser_type {
	command,
	arg,
	oper,
	redir,
	pipe_ch,
	file
}	t_sparser_type;

typedef struct s_lexer_data
{
	char				*text;
	t_lexer_type		lexer_type;
	struct s_lexer_data	*next;
}		t_lexer_data;

typedef struct s_parser_data
{
	char					*text;
	t_lexer_type			lexer_type;
	char					**cmd_line;
	char					*red_stdin;
	char					*red_stdout;
	struct s_parser_data	*parent;
	struct s_parser_data	*left;
	struct s_parser_data	*right;
}		t_parser_data;

typedef struct s_env
{
	char			*var;
	char			*value;
	struct s_env	*next;
}		t_env;

typedef struct data
{
	t_lexer_data	*lexer_data;
	t_parser_data	*parser_data;
	t_env			*env_vars;
	t_env			*env_del;
}			t_data;

void			init_data(t_data *data);

void			destroy_data(t_data *data);

void			lexer(t_data *data, char *cmd_buff);

t_lexer_data	*add_lexer_node(t_data *data, char *text);

void			delete_lexer_data(t_data *data);

void			tokenizer(t_lexer_data *lexer_node);

int				create_process(int *fd1, int *fd2);

void			child_signals(int signum);

void			dismiss_signal(int signum);

void			config_signals(void);

t_lexer_data	*get_last_lexer_node(t_data *data);

void			build_tree(t_data *data, char **oper_arr);

void			syntax_parser(t_data *data);

void			executor(t_data *data);

#endif
