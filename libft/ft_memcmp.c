/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 20:15:18 by nallani           #+#    #+#             */
/*   Updated: 2018/10/14 23:14:57 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s, const void *s2, size_t n)
{
	size_t			i;
	char			*adds;
	char			*adds2;

	i = 0;
	adds = (void *)s;
	adds2 = (void *)s2;
	while (i < n)
	{
		if ((unsigned char)adds[i] != (unsigned char)(adds2[i]))
			return ((unsigned char)adds[i] - (unsigned char)adds2[i]);
		i++;
	}
	return (0);
}
