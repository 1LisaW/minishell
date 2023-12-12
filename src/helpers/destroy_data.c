/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 21:03:01 by tklimova          #+#    #+#             */
/*   Updated: 2023/12/12 15:07:07 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_shell.h"

void	ft_destroy_env(t_env **envv)
{
	t_env	*curr_env;

	while (envv
		&& (*envv))
	{
		curr_env = (*envv)->next;
		if ((*envv)->var)
			free((*envv)->var);
		(*envv)->var = NULL;
		if ((*envv)->value)
			free((*envv)->value);
		(*envv)->value = NULL;
		free((*envv));
		*envv = curr_env;
	}
}
