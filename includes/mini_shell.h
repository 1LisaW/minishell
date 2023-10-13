/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:58:51 by tklimova          #+#    #+#             */
/*   Updated: 2023/10/11 10:53:30 by plandolf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H
# define IS_WAIT 0x1
# define IS_PIPE 0x2
# define IS_LAST_PIPE_CMD 0x3

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
# include <dirent.h>
# include <sys/wait.h>

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
	int						flags;
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
	int				pipes_amount;
}			t_data;

void			init_data(t_data *data);

void			destroy_data(t_data *data);

void			lexer(t_data *data, char *cmd_buff);

t_lexer_data	*add_lexer_node(t_data *data, char *text);

void			delete_lexer_data(t_data *data);

void			tokenizer(t_lexer_data *lexer_node);

void			child_signals(int signum);

void			dismiss_signal(int signum);

void			config_signals(void);

void			ft_init_env(char **envp, t_data *data);

void			add_env(char *var, char *value, t_data *data);

char			*get_env(char *text, t_data *data);

void			set_env(char *var, char *value, t_data *data);

void			unset_var(char *var, t_data *data);

char			*get_path(char *text, t_data *data);

//builtins
int				pwd(void);
int				cd(char **args, t_data *env);
int				echo(char **args);

t_lexer_data	*get_last_lexer_node(t_data *data);

void			build_tree(t_data *data, char **oper_arr);

void			syntax_parser(t_data *data);

void			execute_process(int *prev_fd, t_parser_data *parser_node);

void			executor(t_data *data);

#endif
