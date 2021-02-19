/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 18:09:35 by nallani           #+#    #+#             */
/*   Updated: 2018/10/21 20:03:29 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	ft_fillit(char const *s, char c, char **str, int k)
{
	size_t		i;
	int			j;

	i = 0;
	j = -1;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		j++;
		if (s[i] != '\0')
		{
			while (s[i] != c && s[i] != '\0')
				str[j][++k] = s[i++];
			str[j][++k] = '\0';
		}
		k = -1;
		if (s[i] != '\0')
			i++;
	}
}

static	short	ft_count_char(char const *s, char c, char **str, int k)
{
	size_t	i;
	int		j;

	i = 0;
	j = 1;
	while (s[i])
	{
		while (s[i] != c && s[i] != '\0')
		{
			i++;
			j++;
		}
		if (j > 1 || s[i] == '\0')
		{
			if (!(str[k] = (char *)malloc(sizeof(char) * j)))
				return (k);
			j = 1;
			k++;
		}
		if (s[i] != '\0')
			i++;
	}
	str[k] = 0;
	return (-1);
}

static	size_t	ft_count_tab(char const *s, char c)
{
	size_t	i;
	int		j;

	i = 0;
	j = 1;
	while (s[i])
	{
		if (s[i] != c)
		{
			j++;
			while (s[i] != '\0' && s[i] != c)
				i++;
			if (s[i] == '\0')
				return (j);
		}
		i++;
	}
	return (j);
}

static	char	**ft_back0(char const *s)
{
	size_t	i;
	char	**str;

	i = 0;
	if (!(str = (char **)malloc(sizeof(char *) * 2)))
		return (NULL);
	if (!(str[0] = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1))))
		return (NULL);
	if (!(str[1] = (char *)malloc(sizeof(char) * 1)))
		return (NULL);
	while (s[i])
	{
		str[0][i] = (char)s[i];
		i++;
	}
	str[1] = 0;
	return (str);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**str;
	size_t	j;
	short	k;

	if (!s)
		return (NULL);
	if (c == '\0')
		return (ft_back0(s));
	j = ft_count_tab(s, c);
	if (!(str = (char **)malloc(sizeof(char *) * j)))
		return (NULL);
	if ((k = ft_count_char(s, c, str, 0)) != -1)
	{
		while (k-- > 0)
			free(str[k]);
		free(str);
		return (NULL);
	}
	ft_fillit(s, c, str, -1);
	return (str);
}
