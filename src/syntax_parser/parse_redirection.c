/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:38:23 by tklimova          #+#    #+#             */
/*   Updated: 2023/10/18 17:13:38 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

t_redir_data	*create_redir_node(t_lexer_data *lexer_node)
{
	t_redir_data	*redir_node;

	redir_node = malloc(sizeof(t_redir_data));
	if (!redir_node)
		return (NULL);
	redir_node->std_fd = 0;
	redir_node->is_here_doc = 0;
	if (!strcmp(lexer_node->text, ">") || (!strcmp(lexer_node->text, ">>")))
		redir_node->std_fd += 1;
	if (!strcmp(lexer_node->text, "<"))
		redir_node->flags = F_OK | O_RDONLY;
	else if (!strcmp(lexer_node->text, "<<"))
	{
		redir_node->flags = 0x0;
		redir_node->is_here_doc = 1;
	}
	else if (!strcmp(lexer_node->text, ">"))
		redir_node->flags = O_CREAT | O_WRONLY | O_TRUNC;
	else if (!strcmp(lexer_node->text, ">>"))
		redir_node->flags = O_CREAT | O_WRONLY | O_APPEND;
	redir_node->next = NULL;
	return (redir_node);
}

t_lexer_data	*ft_add_redir_node(t_lexer_data *lexer_node,
		t_parser_data *parser_node)
{
	t_redir_data	*redir_node;

	redir_node = NULL;
	if (!lexer_node || lexer_node->lexer_type != redir_notation)
		return (lexer_node);
	if (!parser_node->redir_data)
	{
		parser_node->redir_data = create_redir_node(lexer_node);
		redir_node = parser_node->redir_data;
	}
	else
	{
		redir_node = parser_node->redir_data;
		while (redir_node->next)
			redir_node = redir_node->next;
		redir_node->next = create_redir_node(lexer_node);
		redir_node = redir_node->next;
	}
	lexer_node = lexer_node->next;
	if (lexer_node && lexer_node->lexer_type == word)
	{
		redir_node->text = ft_strcopy(lexer_node->text);
		lexer_node = lexer_node->next;
	}
	return (lexer_node);
}

t_lexer_data	*collect_redir(t_lexer_data *lexer_node,
	t_parser_data *parser_node)
{
	while (lexer_node && lexer_node->lexer_type == redir_notation)
		lexer_node = ft_add_redir_node(lexer_node, parser_node);
	return (lexer_node);
}

void	destroy_redir_lst(t_parser_data *parser_data)
{
	t_redir_data	*redir_node;

	redir_node = NULL;
	if (!parser_data)
		return ;
	while (parser_data->redir_data)
	{
		redir_node = parser_data->redir_data->next;
		if (parser_data->redir_data->text)
			free(parser_data->redir_data->text);
		parser_data->redir_data->text = NULL;
		free(parser_data->redir_data);
		parser_data->redir_data = redir_node;
	}
	parser_data->redir_data = NULL;
}
