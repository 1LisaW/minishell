/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pascal <pascal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 22:39:39 by pascal            #+#    #+#             */
/*   Updated: 2023/12/13 22:39:52 by pascal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

bool	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	if (!(s1 || !s2 || !n))
		return (0);
	while (n--)
	{
		if (*(unsigned char *)s1 != *(unsigned char *)s2)
			return (1);
		s1++;
		s2++;
	}
	return (0);
}
