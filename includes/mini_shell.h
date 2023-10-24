/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plandolf <plandolf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:58:51 by tklimova          #+#    #+#             */
/*   Updated: 2023/10/24 15:23:12 by plandolf         ###   ########.fr       */
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
# include <dirent.h>
# include <stdbool.h>

typedef enum e_lexer_type {
	word,
	operator,
	redir_notation
}	t_lexer_type;

typedef enum e_parser_type {
	command,
	arg,
	oper,
	redir,
	pipe_ch,
	file
}	t_parser_type;

typedef struct s_lexer_data
{
	char				*text;
	t_lexer_type		lexer_type;
	struct s_lexer_data	*next;
}		t_lexer_data;

typedef struct s_parser_data
{
	char					*text;
	t_parser_type			parser_type;
	char					*operator;
	struct s_parser_data	*pipeline;
	char					*red_stdin;
	char					*red_stdout;
	struct s_parser_data	*next;
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

typedef struct s_ptrs 
{
	char	*temp;
	char	*r_ptr;
	char	*w_ptr;
}				t_ptrs;

void			init_data(t_data *data);

void			destroy_data(t_data *data);

void			lexer(t_data *data, char *cmd_buff);

t_lexer_data	*add_lexer_node(t_data *data, char *text);

void			delete_lexer_data(t_lexer_data *lexer_data);

void			tokenizer(t_lexer_data *lexer_node);

int				create_process(int *fd1, int *fd2);

void			child_signals(int signum);

void			dismiss_signal(int signum);

void			config_signals(void);

void			ft_init_env(char **envp, t_data *data);

void			add_env(char *var, char *value, t_data *data);

char			*get_env(char *text, t_data *data);

void			set_env(char *var, char *value, t_data *data);

void			unset_var(char *var, t_data *data);

char			*get_path(char *text, t_data *data);

void			modify_cmd(char *str, t_data *data);

//builtins
int				pwd(void);
int				cd(char **args, t_data *env);
int				echo(char **args);

//modif_cmd
void process_char(t_ptrs *ptrs, bool *in_single_quotes, t_data *data);
void	modify_cmd(char *str, t_data *data);
char	*copy_variable_name(char **r_ptr, char *variable_name);
void	write_replacement_or_variable(char **w_ptr, char *variable_name,
	t_data *data);
char	*copy_var_and_get_next(char *r_ptr, char **w_ptr, t_data *data);
void handle_quotes(char **r_ptr, char **w_ptr, bool *in_single_quotes);
void	init_pointers(t_ptrs *ptrs, char *str, bool *in_single_quotes);

#endif
