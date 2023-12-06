/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutate_cmd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:23:43 by tklimova          #+#    #+#             */
/*   Updated: 2023/12/06 16:36:33 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

void	concat_str(char **res, char *str, int *len)
{
	char	*tmp;

	if (!str || !(*str))
		return ;
	tmp = ft_strjoin(*res, str);
	*len += ft_strlen(str);
	free(str);
	free(*res);
	*res = tmp; 
}