/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/14 18:18:17 by nallani           #+#    #+#             */
/*   Updated: 2018/10/24 13:57:13 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Commence a compter a partir de 0
*/

void	ft_lstaddat(t_list **alst, t_list *new, size_t pos)
{
	t_list	*tmp;

	if (alst && new)
	{
		tmp = *alst;
		if (pos == 0 || !(tmp))
			ft_lstadd(alst, new);
		else if (tmp)
		{
			while (tmp && --pos > 0)
				tmp = tmp->next;
			new->next = tmp->next;
			tmp->next = new;
		}
	}
}
