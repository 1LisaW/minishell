/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:58:51 by tklimova          #+#    #+#             */
/*   Updated: 2023/12/31 12:45:00 by tklimova         ###   ########.fr       */
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
# include <stdbool.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <stdarg.h>

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
	t_lexer_data			*lexer_data;
	t_parser_data			*parser_data;
	t_env					*env_vars;
	t_env					*env_del;
	struct s_exec_data		*exec_data;
	int						status_code;
}			t_data;

typedef struct s_ptrs
{
	char	*temp;
	char	*r_ptr;
	char	*w_ptr;
}				t_ptrs;

typedef struct s_exec_data
{
	int		status_code;
	int		stdin_dup;
	int		stdout_dup;
	int		was_stdinredir;
	int		was_stdoutredir;
	char	*here_doc;
	int		go_on;
	int		fd_out;
	char	*err_file;
	int		ctrl_c;
	t_data	*link_to_data;
}			t_exec_data;

typedef struct s_gb
{
	int		exit_st;
}	t_gb;

void			init_data(t_data *data);

void			destroy_redir_lst(t_parser_data *parser_node);

void			destroy_data(t_data *data);

void			lexer(t_data *data, char *cmd_buff);

t_lexer_data	*add_lexer_node(t_data *data, char *text);

void			delete_lexer_data(t_data *data);

void			tokenizer(t_lexer_data *lexer_node);

void			child_signals(int signum);

//SIGNALS

void			handle_cmd_signal(int sig);

void			config_signals(void);

void			handle_cmd_signals(void);

//ERROR
void			set_error_code(int err_code);

int				get_error(void);

void			ft_init_env(char **envp, t_env **envv);

void			ft_destroy_env(t_env **envv);

void			add_env(char *var, char *value, t_env **envv);

char			*get_env_value(char *text, t_env *envv);

void			set_env(char *var, char *value, t_env **envv);

void			unset_var(char *var, t_env **envv);

char			*get_path(char *text, t_env *envv);

void			modify_cmd(char *ret, char *s, t_env *env);

void			ft_update_for_empty_cmd(t_parser_data *parser_node);

void			mutate_parser_node(t_parser_data *s_parser_data, t_data *data);

//builtins
int				pwd(void);
int				cd(char **args);
int				echo(char **cmd);
int				env(char **argv);
int				unset(char **cmd);
int				exit_builtin(t_parser_data *data);
int				export(char **cmd);

//env get set

void			set_envv(t_env *envv);

t_env			*get_envv(void);

char			*get_env_var(void);

char			**env_list_to_array(t_env *env_list);

//envp get set

void			set_envp(char **envp);

char			**get_envp(void);

//modif_cmd
void			process_char(t_ptrs *ptrs, bool *in_single_quotes, t_env *env);

char			*copy_variable_name(char **r_ptr, char *variable_name);

void			write_replacement_or_variable(char **w_ptr, char *variable_name,
					t_env *env);

char			*copy_var_and_get_next(char *r_ptr, char **w_ptr, t_env *env);

void			handle_quotes(char **r_ptr, char **w_ptr,
					bool *in_single_quotes);

void			init_pointers(t_ptrs *ptrs, char *str, bool *in_single_quotes);

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

void			clear_exec_data(t_exec_data *exec_data);

void			change_redir_data_without_cmd(t_parser_data *parser_node);

void			make_redirections(t_parser_data *parser_node,
					t_exec_data *exec_data, int *prev_fd);

void			make_redir_without_cmd(t_parser_data *parser_node,
					t_exec_data *exec_data);

void			clear_savedstd(t_exec_data *exec_data);

int				create_process(int *prev_fd, t_parser_data *parser_node,
					t_exec_data *exec_data);

void			command_not_found(char *cmd);

void			bind_current_path_to_cmd(t_parser_data *parser_node,
					t_env *env);

void			ft_set_gb_status_code(t_exec_data *exec_data);

int				ft_response_bad_execve(char *cmd);

void			executor(t_data *data);

bool			is_identifier(int c);

char			*expand_var(char *s, int *i, t_env *env);

int				exit_with_status(int exit_status);

int				check_next_quote(char *s, char c);

void			should_expnd(bool *flg);

int				calc_len(char *s);

void			eliminate_quotes_phase(char **args);

void			*malloc_error(int errnum);

void			print_error(int n, ...);

char			*new_cmd(char *s, bool *flg);

void			expand_and_modify(void);

int				calc_len(char *s);

void			calc_len_after_env_replacement(int *len, char *str, t_env *env);

bool			is_builtin(char *cmd);

int				exec_builtins(t_parser_data *token);

void			free_env(t_env *env);

bool			identifier_front(int c);

void			export_var(char *s, char c);

ssize_t			find_c(char *s, char c);

extern t_gb	g_gb;

#endif
