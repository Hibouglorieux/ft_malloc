/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 20:06:21 by nallani           #+#    #+#             */
/*   Updated: 2018/10/14 23:15:12 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	char	*add;

	add = (char*)s;
	i = 0;
	while (i < n)
	{
		if ((unsigned char)add[i] == (unsigned char)c)
			return (&add[i]);
		i++;
	}
	return (NULL);
}
