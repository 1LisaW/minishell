/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:11:22 by tklimova          #+#    #+#             */
/*   Updated: 2023/11/21 15:42:28 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

int	get_next_node(t_parser_data **curr_node, t_parser_data **prev_node)
{
	*prev_node = (*curr_node)->left;
	while ((*prev_node)->right && (*prev_node)->right != *curr_node)
		*prev_node = (*prev_node)->right;
	if (!(*prev_node)->right)
	{
		(*prev_node)->right = *curr_node;
		*curr_node = (*curr_node)->left;
		return (0);
	}
	return (1);
}

void	check_prolong(t_parser_data *parser_node, t_exec_data *exec_data)
{
	if (!ft_strcmp(parser_node->text, "&&") && exec_data->status_code)
		exec_data->go_on = 0;
	if (!ft_strcmp(parser_node->text, "||") && !exec_data->status_code)
		exec_data->go_on = 0;
}

void	execute_process(int *prev_fd, t_parser_data *parser_node,
			t_exec_data *exec_data)
{
	t_parser_data	*temp;

	temp = parser_node;
	printf("\n NO_DE:%s, %i\n",
		parser_node->text, parser_node->lexer_type);
	make_redir_without_cmd(parser_node, exec_data);
	if (parser_node->lexer_type == operator)
		return (check_prolong(parser_node, exec_data));
	if (parser_node->lexer_type == word)
		create_process(prev_fd, parser_node, exec_data);
	if (parser_node->flags & IS_WAIT)
	{
		printf("\n Waiting for execution in	execute_process:%s\n",
			parser_node->text);
		while (wait(NULL) != -1)
			;
	}
}

void	morris_traversal(t_parser_data *parser_data, int *prev_fd,
			t_exec_data *exec_data)
{
	t_parser_data	*curr_node;
	t_parser_data	*prev_node;

	curr_node = parser_data;
	while (curr_node && exec_data->go_on)
	{
		if (!curr_node->left)
		{
			execute_process(prev_fd, curr_node, exec_data);
			curr_node = curr_node->right;
		}
		else if (get_next_node(&curr_node, &prev_node))
		{
			prev_node->right = NULL;
			execute_process(prev_fd, curr_node, exec_data);
			curr_node = curr_node->right;
		}
	}
}

void	executor(t_data *data)
{
	int			prev_fd;
	t_exec_data	exec_data[1];

	init_exec_data(exec_data);
	prev_fd = dup(STDIN_FILENO);
	morris_traversal(data->parser_data, &prev_fd, exec_data);
	clear_exec_data(exec_data, data);
	close(prev_fd);
}
