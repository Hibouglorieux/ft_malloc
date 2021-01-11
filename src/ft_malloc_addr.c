/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_addr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 09:30:02 by nathan            #+#    #+#             */
/*   Updated: 2021/01/11 09:45:35 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

t_block	*get_first_block(size_t size)
{
	size_t page_size;

	page_size = getpagesize();
	if (size == page_size * 4)
		return (get_g_mallocs()->tiny);
	if (size == page_size * 16)
		return (get_g_mallocs()->small);
	else
		return (get_g_mallocs()->large);
}

t_allocated	*get_first_allocated(t_block* block)
{
	return (t_allocated*)((void*)block + sizeof(t_block));
}

t_allocated	*user_to_allocated(void *ptr)
{
	return (t_allocated*)((void*)ptr - sizeof(t_allocated));
}

void	*allocated_to_user(t_allocated *allocated)
{
	return (void*)((void*)allocated + sizeof(t_allocated));
}

t_allocated		*get_last_allocated(t_block *block)//TODO super unsafe
{
	t_allocated		*tmp;

	if (!block)
		return (NULL);
	tmp = get_first_allocated(block);
	if (!tmp)
		return (NULL);
	while (tmp->next != NULL)
		tmp = tmp->next;
	return tmp;
}
