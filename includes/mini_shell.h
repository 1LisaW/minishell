/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:58:51 by tklimova          #+#    #+#             */
/*   Updated: 2023/10/24 15:25:32 by tklimova         ###   ########.fr       */
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
# include <fcntl.h>
# include <errno.h>

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

typedef struct s_redir_data
{
	int					std_fd;
	int					flags;
	char				*text;
	int					is_here_doc;
	struct s_redir_data	*next;
}		t_redir_data;

typedef struct s_parser_data
{
	char					*text;
	t_lexer_type			lexer_type;
	char					**cmd_line;
	int						flags;
	t_redir_data			*redir_data;
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

typedef struct s_data
{
	t_lexer_data	*lexer_data;
	t_parser_data	*parser_data;
	t_env			*env_vars;
	t_env			*env_del;
	int				status_code;
}			t_data;

typedef struct s_exec_data
{
	int		status_code;
	int		stdin_dup;
	int		stdout_dup;
	int		was_stdinredir;
	int		was_stdoutredir;
	char	*here_doc;
	int		go_on;
	// int		fd_in;
	int		fd_out;
}			t_exec_data;

void			init_data(t_data *data);

void			destroy_redir_lst(t_parser_data *parser_node);

void			destroy_data(t_data *data);

void			lexer(t_data *data, char *cmd_buff);

t_lexer_data	*add_lexer_node(t_data *data, char *text);

void			delete_lexer_data(t_data *data);

void			tokenizer(t_lexer_data *lexer_node);

void			child_signals(int signum);

void			dismiss_signal(int signum);

void			config_signals(void);

void			ft_init_env(char **envp, t_env **envv);

void			add_env(char *var, char *value, t_env **envv);

char			*get_env(char *text, t_env *envv);

void			set_env(char *var, char *value, t_env **envv);

void			unset_var(char *var, t_env **envv);

char			*get_path(char *text, t_env *envv);

//builtins
int				pwd(void);
int				cd(char **args, t_env *env);
int				echo(char **args);

t_lexer_data	*get_last_lexer_node(t_data *data);

t_lexer_data	*collect_redir(t_lexer_data *lexer_node,
					t_parser_data *parser_node);

t_parser_data	*create_parser_node(t_lexer_data *lexer_node,
					t_parser_data *parent);

void			build_tree(t_data *data, char **oper_arr);

void			syntax_parser(t_data *data);

void			init_exec_data(t_exec_data *exec_data);

void			reset_std(t_exec_data *exec_data, int fd);

void			here_doc(t_exec_data *exec_data, t_redir_data *redir_data,
					int *prev_fd);

void 			clear_exec_data(t_exec_data *exec_data, t_data *data);

void			make_redirections(t_parser_data *parser_node,
					t_exec_data *exec_data, int *prev_fd);

void			clear_savedstd(t_exec_data *exec_data);

void			execute_process(int *prev_fd, t_parser_data *parser_node,
					t_exec_data *exec_data);

void			executor(t_data *data);

#endif
