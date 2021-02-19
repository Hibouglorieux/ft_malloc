/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 19:11:44 by nallani           #+#    #+#             */
/*   Updated: 2018/10/14 23:15:26 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*adddest;
	char	*addsrc;

	adddest = (char *)dst;
	addsrc = (char *)src;
	i = 0;
	while (i < n)
	{
		adddest[i] = addsrc[i];
		i++;
	}
	return (dst);
}
