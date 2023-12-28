/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 16:29:14 by tklimova          #+#    #+#             */
/*   Updated: 2023/12/20 10:58:35 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

// check errors when command line begins or ends with operator character
//	or have sequences of operators without commands between them

char	*catch_syntax_error(t_lexer_data *lexer_data)
{
	t_lexer_data	*curr_lex_data;

	if (lexer_data->lexer_type == operator)
		return (lexer_data->text);
	curr_lex_data = lexer_data;
	while (curr_lex_data->next)
	{
		if ((curr_lex_data->lexer_type == operator
				&& curr_lex_data->next->lexer_type == operator)
			|| (curr_lex_data->lexer_type == redir_notation
				&& curr_lex_data->next->lexer_type != word))
			return (lexer_data->next->text);
		curr_lex_data = curr_lex_data->next;
	}
	if (curr_lex_data->lexer_type == operator)
		return (curr_lex_data->text);
	return (NULL);
}

char	**get_oper_arr(char **oper_arr)
{
	oper_arr[0] = ft_strcopy("&&");
	oper_arr[1] = ft_strcopy("||");
	oper_arr[2] = ft_strcopy("|");
	oper_arr[3] = NULL;
	return (oper_arr);
}

void	syntax_parser(t_data *data)
{
	char	*syntax_error;
	char	**oper_arr;

	if (!data->lexer_data)
		return ;
	syntax_error = catch_syntax_error(data->lexer_data);
	if (syntax_error)
	{
		perror("syntax error near unexpected token");
		perror(syntax_error);
		return ;
	}
	oper_arr = malloc(sizeof(char *) * 4);
	if (!oper_arr)
		return ;
	build_tree(data, get_oper_arr(oper_arr));
	executor(data);
}
