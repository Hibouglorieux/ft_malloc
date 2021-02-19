/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 19:09:14 by nallani           #+#    #+#             */
/*   Updated: 2018/10/14 23:09:17 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (haystack[++i])
	{
		while (haystack[i++] == needle[j++])
			if (needle[j] == '\0')
				return ((char *)&haystack[i - j]);
		i -= j;
		j = 0;
	}
	return (NULL);
}
