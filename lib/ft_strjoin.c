/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plandolf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 14:50:58 by plandolf          #+#    #+#             */
/*   Updated: 2023/09/28 10:31:23 by plandolf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new_s;
	int		i;
	int		l;

	i = 0;
	l = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	new_s = malloc((ft_strlen(s1) + ft_strlen(s2)) * sizeof(char) + 1);
	if (!new_s)
		return (NULL);
	while (s1[i])
		new_s[l++] = s1[i++];
	i = 0;
	while (s2[i])
		new_s[l++] = s2[i++];
	new_s[l] = '\0';
	return (new_s);
}
