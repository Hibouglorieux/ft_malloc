/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 17:52:20 by nallani           #+#    #+#             */
/*   Updated: 2018/10/14 23:00:19 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *tmp;

	if (alst && del)
	{
		tmp = *alst;
		while (tmp)
		{
			*alst = tmp->next;
			del(tmp->content, tmp->content_size);
			free(tmp);
			tmp = *alst;
		}
		alst = NULL;
	}
}
