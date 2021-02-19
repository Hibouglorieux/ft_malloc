/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 19:56:18 by nallani           #+#    #+#             */
/*   Updated: 2018/10/14 23:14:50 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*adddst;
	char	*addsrc;
	size_t	i;

	i = 0;
	adddst = (char *)dst;
	addsrc = (char *)src;
	if (adddst > addsrc)
		while (len > 0)
		{
			len--;
			adddst[len] = addsrc[len];
		}
	if (adddst < addsrc)
		while (i < len)
		{
			adddst[i] = addsrc[i];
			i++;
		}
	return (dst);
}
