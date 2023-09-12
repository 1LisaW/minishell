/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:58:51 by tklimova          #+#    #+#             */
/*   Updated: 2023/09/12 14:49:53 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include "../lib/lib.h"
# include <unistd.h>
# include <sys/types.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

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

int		create_process(int *fd1, int *fd2);

#endif
