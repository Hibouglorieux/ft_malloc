/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 18:13:17 by nallani           #+#    #+#             */
/*   Updated: 2021/02/19 04:14:40 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	t_list	*ft_cancelmap(t_list **lst)
{
	t_list	*tmp;

	while (*lst)
	{
		tmp = *lst;
		free(tmp->content);
		tmp->content_size = 0;
		*lst = (*lst)->next;
		free(tmp);
	}
	return (NULL);
}

t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list			*new;
	t_list			*addnew;
	t_list			*lst2;

	if (!(lst) || !(f))
		return (NULL);
	if (!(new = ft_lstnew(lst->content, lst->content_size)))
		return (NULL);
	if (!(new = f(new)))
		return (ft_cancelmap(&lst2));
	lst2 = new;
	while (lst->next)
	{
		lst = lst->next;
		if (!(addnew = ft_lstnew(lst->content, lst->content_size)))
			return (ft_cancelmap(&lst2));
		if (!(addnew = f(addnew)))
			return (ft_cancelmap(&lst2));
		new->next = addnew;
		new = new->next;
	}
	new->next = NULL;
	return (lst2);
}
