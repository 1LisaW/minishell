/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:11:22 by tklimova          #+#    #+#             */
/*   Updated: 2023/12/12 15:23:10 by tklimova         ###   ########.fr       */
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

void	check_prolong(t_parser_data *parser_node,
				t_exec_data *exec_data, int *prev_fd)
{
	if (!ft_strcmp(parser_node->text, "&&") && exec_data->status_code)
		exec_data->go_on = 0;
	if (!ft_strcmp(parser_node->text, "||") && !exec_data->status_code)
		exec_data->go_on = 0;
	if (exec_data->go_on && ft_strcmp(parser_node->text, "|"))
	{
		printf("[LOG] %i",*prev_fd);
		// perror("\n[LOG] GOON\n %i");
	}
}

void	execute_process(int *prev_fd, t_parser_data *parser_node,
			t_exec_data *exec_data, t_data *data)
{
	mutate_parser_node(parser_node, data);
	if (parser_node->lexer_type == redir_notation)
		make_redir_without_cmd(parser_node, exec_data);
	if (parser_node->lexer_type == operator)
		return (check_prolong(parser_node, exec_data, prev_fd));
	if (parser_node->lexer_type == word)
	{
		if (ft_strcmp(parser_node->text, "pwd"))
			bind_current_path_to_cmd(parser_node, data->env_vars);
		create_process(prev_fd, parser_node, exec_data);
	}
	if (parser_node->flags & IS_WAIT)
	{
		while (wait(NULL) != -1)
			;
	}
}

void	morris_traversal(t_data *data, int *prev_fd,
			t_exec_data *exec_data)
{
	t_parser_data	*curr_node;
	t_parser_data	*prev_node;

	curr_node = data->parser_data;
	while (curr_node && exec_data->go_on)
	{
		if (!curr_node->left)
		{
			execute_process(prev_fd, curr_node, exec_data, data);
			curr_node = curr_node->right;
		}
		else if (get_next_node(&curr_node, &prev_node))
		{
			prev_node->right = NULL;
			execute_process(prev_fd, curr_node, exec_data, data);
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
	morris_traversal(data, &prev_fd, exec_data);
	clear_exec_data(exec_data, data);
	close(prev_fd);
}
