/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 13:28:25 by root              #+#    #+#             */
/*   Updated: 2023/12/12 13:54:44 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

int	get_oper_length(char quote, char *str)
{
	if (quote)
		return (0);
	if (!ft_strncmp(str, "||", 2) || !ft_strncmp(str, "&&", 2)
		|| !ft_strncmp(str, "<<", 2) || !ft_strncmp(str, ">>", 2))
		return (2);
	if (!ft_strncmp(str, "|", 1) || !ft_strncmp(str, "<", 1)
		|| !ft_strncmp(str, ">", 1))
		return (1);
	return (0);
}

void	get_word_len(char *cmd_buff, int *w_len)
{
	char	sep;
	char	quote;

	sep = ' ';
	quote = '\0';
	*w_len = 0;
	*w_len = get_oper_length(quote, cmd_buff);
	if (*w_len)
		return ;
	while (cmd_buff[*w_len])
	{
		if (!quote && cmd_buff[*w_len] == '\'')
			quote = '\'';
		else if (!quote && cmd_buff[*w_len] == '\"')
			quote = '\"';
		else if (quote && (cmd_buff[*w_len] == quote))
			quote = 0;
		(*w_len)++;
		if ((cmd_buff[*w_len] == sep
				|| get_oper_length(quote, cmd_buff + *w_len)) && !quote)
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
		cmd_buff += w_len;
	}
	syntax_parser(data);
	printf("\nDESTROY!!!!\n");
	destroy_data(data);
}
