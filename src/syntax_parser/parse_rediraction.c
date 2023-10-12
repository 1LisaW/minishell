/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rediraction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:38:23 by tklimova          #+#    #+#             */
/*   Updated: 2023/10/12 15:49:01 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

t_lexer_data	*collect_redir(t_lexer_data *lexer_node,
	t_parser_data *parser_node)
{
	if (lexer_node && lexer_node->lexer_type != redir_notation)
		return (lexer_node);
	if (!strcmp(lexer_node->text, "<"))
		parser_node->stdin_flag = 1;
	else if (!strcmp(lexer_node->text, "<<"))
		parser_node->stdin_flag = 2;
	else if (!strcmp(lexer_node->text, ">"))
		parser_node->stdout_flag = 1;
	else if (!strcmp(lexer_node->text, ">>"))
		parser_node->stdout_flag = 2;
	lexer_node = lexer_node->next;
	if (!strcmp(lexer_node->text, "<") || !strcmp(lexer_node->text, "<<"))
		parser_node->red_stdin = ft_strcpy(lexer_node->text);
	else
		parser_node->red_stdout = ft_strcpy(lexer_node->text);
	lexer_node = lexer_node->next;
	return (lexer_node);
}