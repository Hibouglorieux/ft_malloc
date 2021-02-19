/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 16:02:26 by nallani           #+#    #+#             */
/*   Updated: 2018/10/07 21:14:15 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*ft_itoa_2(long n, char *str, short neg, int j)
{
	if (neg == 1)
	{
		str[0] = '-';
		n = -n;
	}
	str[--j] = '\0';
	if (n == 0)
		str[--j] = 48;
	while (n > 0)
	{
		str[--j] = n % 10 + 48;
		n /= 10;
	}
	return (str);
}

char			*ft_itoa(int n)
{
	char	*str;
	long	i;
	int		j;
	short	neg;

	i = n;
	j = 2;
	neg = 0;
	if (n < 0)
	{
		j++;
		neg = 1;
	}
	while (n < -9 || n > 9)
	{
		n /= 10;
		j++;
	}
	if (!(str = (char *)malloc(sizeof(char) * j)))
		return (NULL);
	return (ft_itoa_2(i, str, neg, j));
}
