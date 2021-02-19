/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 20:32:40 by nallani           #+#    #+#             */
/*   Updated: 2018/10/21 17:01:32 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstrev(t_list **alst)
{
	t_list	*tmp2;
	t_list	*tmp3;

	if (alst && *alst && (*alst)->next)
	{
		tmp2 = (*alst)->next;
		(*alst)->next = NULL;
		tmp3 = tmp2;
		if (!tmp3->next)
		{
			tmp2->next = *alst;
			*alst = tmp3;
			return ;
		}
		while (tmp3->next)
		{
			tmp2 = tmp3;
			tmp3 = tmp2->next;
			tmp2->next = *alst;
			*alst = tmp2;
		}
		tmp3->next = tmp2;
		*alst = tmp3;
	}
}
