/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:59:49 by tklimova          #+#    #+#             */
/*   Updated: 2023/09/11 20:14:21 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_shell.h"

void	minishell(void)
{
	char	*cmd_buff;

	while (1)
	{
		cmd_buff = readline("minishell> ");
		if (ft_strlen(cmd_buff) > 0)
			add_history(cmd_buff);
		if (!ft_strcmp(cmd_buff, "exit"))
			break;
	}
}

int	main(void)
{
	minishell();
	return (0);
}
