/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 18:30:31 by nallani           #+#    #+#             */
/*   Updated: 2018/10/14 23:10:38 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	i;

	i = 0;
	while (len > 0)
	{
		if (src[i])
			dst[i] = src[i];
		else
		{
			while (len > 0)
			{
				dst[i] = '\0';
				i++;
				len--;
			}
			continue;
		}
		i++;
		len--;
	}
	return (dst);
}
