/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 20:46:01 by nallani           #+#    #+#             */
/*   Updated: 2018/10/09 19:21:57 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*ft_only_spaces(void)
{
	char	*str;

	if (!(str = (char *)malloc(sizeof(char) * 1)))
		return (NULL);
	str[0] = '\0';
	return (str);
}

static	char	*ft_fillit(char const *s, size_t start, size_t end)
{
	size_t		i;
	char		*str;

	if (!(str = (char *)malloc(sizeof(char) * (end - start) + 2)))
		return (NULL);
	i = 0;
	while (start <= end)
		str[i++] = (char)s[start++];
	str[i] = '\0';
	return (str);
}

char			*ft_strtrim(char const *s)
{
	size_t		i;
	size_t		k;

	i = 0;
	if (!s)
		return (NULL);
	while ((s[i] == ' ' || s[i] == '\n' || s[i] == '\t') && s[i])
		i++;
	k = i;
	while (s[i])
		i++;
	if (i == k)
		return (ft_only_spaces());
	if (i > 0 && s[i] != ' ' && s[i] != '\n' && s[i] != '\t')
		i--;
	while (s[i] && i > 0 && (s[i] == ' ' || s[i] == '\n' ||
				s[i] == '\t'))
		i--;
	return (ft_fillit(s, k, i));
}
