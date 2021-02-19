/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 21:25:58 by nallani           #+#    #+#             */
/*   Updated: 2018/10/14 23:11:35 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		i;
	size_t		j;
	size_t		k;

	j = 0;
	i = 0;
	while (src[i])
		i++;
	if (size == 0)
		return (i);
	while (dst[j])
	{
		j++;
		i++;
	}
	if (size < j)
		return (i - j + size);
	i = 0;
	k = j;
	while (j < size - 1 && src[i])
		dst[j++] = src[i++];
	dst[j] = '\0';
	while (src[i])
		i++;
	return (i + k);
}
