/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcopy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:57:25 by tklimova          #+#    #+#             */
/*   Updated: 2023/10/03 13:52:53 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

char	*ft_strcopy(char *str)
{
	char	*dup_str;
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	dup_str = malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!dup_str)
		return (NULL);
	while (str[i])
	{
		dup_str[i] = str[i];
		i++;
	}
	dup_str[i] = '\0';
	return (dup_str);
}
