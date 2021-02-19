/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 09:27:46 by nathan            #+#    #+#             */
/*   Updated: 2021/02/19 00:42:42 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void		defragment_blocks(t_block *block)
{
	t_block			*empty;
	unsigned long	available_size_in_blocks;

	empty = NULL;
	available_size_in_blocks = 0;
	while (block != NULL)
	{
		if (block->size_used <= sizeof(t_block))
			empty = block;
		else
			available_size_in_blocks = available_size_in_blocks +
				block->size_allocated - block->size_used;
		block = block->next;
	}
	if (empty && available_size_in_blocks > empty->size_allocated / 8)
		remove_block(empty);
}

static bool	does_pointer_exists_2(t_block *block, t_allocated *alloc_received)
{
	t_allocated	*alloc;

	while (block != NULL)
	{
		alloc = get_first_allocated(block);
		while (alloc)
		{
			if (alloc == alloc_received && alloc->size_queried)
				return (true);
			alloc = alloc->next;
		}
		block = block->next;
	}
	return (false);
}

bool		does_pointer_exists(void *ptr)
{
	t_allocated	*alloc_received;
	t_block		*block;
	int			i;

	if (!ptr)
		return (false);
	if (ptr == NULL || ptr <= (void*)sizeof(t_allocated))
		return (false);
	alloc_received = user_to_allocated(ptr);
	i = -1;
	while (++i < 3)
	{
		if (i == 0)
			block = get_g_mallocs()->tiny;
		else if (i == 1)
			block = get_g_mallocs()->small;
		else
			block = get_g_mallocs()->large;
		if (does_pointer_exists_2(block, alloc_received))
			return (true);
	}
	return (false);
}

void		remove_alloc(t_allocated *removed, t_block *block)
{
	t_allocated	*tmp;

	tmp = get_first_allocated(block);
	if (tmp == removed)
	{
		create_new_alloc(tmp, 0, NULL, removed->next);
	}
	else
	{
		while (tmp->next != removed)
			tmp = tmp->next;
		tmp->next = removed->next;
		removed->size_queried = 0;
		removed->next = NULL;
	}
}

void		free(void *ptr)
{
	t_block		*block;
	t_allocated	*allocated;

	if (secure_malloc())
		return ;
	if (!does_pointer_exists(ptr))
	{
		release_secure_malloc();
		return ;
	}
	allocated = user_to_allocated(ptr);
	block = find_block_containing_alloc(allocated);
	block->size_used = block->size_used -
		align_size_for_address(allocated->size_queried) - sizeof(t_allocated);
	remove_alloc(allocated, block);
	if (get_first_block(block->size_allocated) == get_g_mallocs()->large)
		remove_block(block);
	else
		defragment_blocks(get_first_block(block->size_allocated));
	release_secure_malloc();
}
