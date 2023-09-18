/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 13:48:23 by root              #+#    #+#             */
/*   Updated: 2023/09/18 12:19:35 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

t_lexer_data	*get_last_lexer_node(t_data *data)
{
	t_lexer_data	*lexer_node;

	lexer_node = data->lexer_data;
	if (!lexer_node)
		return (lexer_node);
	while (lexer_node->next)
		lexer_node = lexer_node->next;
	return (lexer_node);
}

t_lexer_data	*add_lexer_node(t_data *data, char *text)
{
	t_lexer_data	*lexer_node;

	if (!data->lexer_data)
	{
		data->lexer_data = malloc(sizeof(t_lexer_data));
		lexer_node = data->lexer_data;
	}
	else
	{
		lexer_node = malloc(sizeof(t_lexer_data));
		get_last_lexer_node(data)->next = lexer_node;
	}
	lexer_node->text = text;
	lexer_node->next = NULL;
	return (lexer_node);
}

void	delete_lexer_data(t_lexer_data *lexer_data)
{
	t_lexer_data	*curr_lexer_node;

	while (lexer_data)
	{
		curr_lexer_node = lexer_data;
		free(curr_lexer_node->text);
		lexer_data = curr_lexer_node->next;
		free(curr_lexer_node);
	}
}
