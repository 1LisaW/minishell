/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 06:26:36 by root              #+#    #+#             */
/*   Updated: 2023/09/18 13:01:58 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

void	tokenizer(t_lexer_data *lexer_node)
{
	if (!ft_strcmp(lexer_node->text, "|") || !ft_strcmp(lexer_node->text, "&&")
		|| !ft_strcmp(lexer_node->text, "||"))
		lexer_node->lexer_type = operator;
	else if (!ft_strcmp(lexer_node->text, "<")
		|| !ft_strcmp(lexer_node->text, "<<")
		|| !ft_strcmp(lexer_node->text, ">")
		|| !ft_strcmp(lexer_node->text, ">>"))
		lexer_node->lexer_type = redir_notation;
	else
		lexer_node->lexer_type = word;
}
