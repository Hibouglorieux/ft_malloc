/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 19:49:17 by nallani           #+#    #+#             */
/*   Updated: 2018/10/14 23:15:17 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	char			*adddst;
	char			*addsrc;

	i = 0;
	adddst = (char *)dst;
	addsrc = (void *)src;
	while (i < n)
	{
		adddst[i] = addsrc[i];
		if ((unsigned char)adddst[i] == (unsigned char)c)
			return (&adddst[i + 1]);
		i++;
	}
	return (NULL);
}
