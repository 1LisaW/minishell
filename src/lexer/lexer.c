/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 13:28:25 by root              #+#    #+#             */
/*   Updated: 2023/10/03 02:31:09 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

void	get_word_len(char *cmd_buff, int *w_len)
{
	char	sep;
	char	quote;

	sep = ' ';
	quote = '\0';
	*w_len = 0;
	while (cmd_buff[*w_len])
	{
		if (!quote && cmd_buff[*w_len] == '\'')
			quote = '\'';
		else if (!quote && cmd_buff[*w_len] == '\"')
			quote = '\"';
		else if (quote && (cmd_buff[*w_len] == quote))
			quote = 0;
		(*w_len)++;
		if (cmd_buff[*w_len] == sep && !quote)
			break ;
	}
}

char	*get_word(char *cmd_buff, int len)
{
	char	*word;

	word = NULL;
	if (!len)
		return (word);
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	word[len] = '\0';
	while (len)
	{
		len--;
		word[len] = cmd_buff[len];
	}
	return (word);
}

void	lexer(t_data *data, char *cmd_buff)
{
	int				w_len;
	t_lexer_data	*lexer_node;
	char			sep;

	sep = ' ';
	while (cmd_buff && *cmd_buff)
	{
		while (*cmd_buff == sep)
			cmd_buff++;
		if (!*cmd_buff)
			break ;
		get_word_len(cmd_buff, &w_len);
		if (w_len)
		{
			lexer_node = add_lexer_node(data, get_word(cmd_buff, w_len));
			tokenizer(lexer_node);
		}
		printf("text: %s, type: %i\n",
			lexer_node->text, lexer_node->lexer_type);
		cmd_buff += w_len;
	}
	syntax_parser(data);
	destroy_data(data);
}
