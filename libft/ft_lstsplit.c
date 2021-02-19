/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 22:26:09 by nallani           #+#    #+#             */
/*   Updated: 2018/10/17 14:27:41 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	ft_while(char *s, size_t *i, size_t *j, char c)
{
	while (s[*i] != c && s[*i] != '\0')
	{
		*i = *i + 1;
		*j = *j + 1;
	}
}

static	void	ft_lstsplit_split(char *s, char c, t_list **alst, size_t f)
{
	size_t	i;
	size_t	j;
	t_list	*tmp;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i] != '\0')
		{
			ft_while(s, &i, &j, c);
			tmp = ft_lstnew(ft_strsub(s, i - j, j), j + 1);
			j = 0;
			if (f++ == 0)
				*alst = tmp;
			ft_lstaddend(alst, tmp);
			tmp->next = NULL;
		}
		if (s[i] != '\0')
			i++;
	}
}

static	void	ft_lstsplitbackzero(char *s, t_list **alst)
{
	size_t	i;
	t_list	*tmp;

	i = 0;
	while (s[i])
		i++;
	tmp = ft_lstnew(s, i + 1);
	*alst = tmp;
}

t_list			*ft_lstsplit(char const *s, char c)
{
	t_list	*alst;

	if (!(s))
		return (NULL);
	if (c == '\0')
	{
		ft_lstsplitbackzero((char *)s, &alst);
		return (alst);
	}
	ft_lstsplit_split((char *)s, c, &alst, 0);
	return (alst);
}
