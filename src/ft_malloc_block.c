/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_block.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 09:46:10 by nathan            #+#    #+#             */
/*   Updated: 2021/01/11 09:48:08 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include <sys/mman.h>

size_t		return_block_size(size_t size)
{
	size_t page_size;

	page_size = getpagesize();
	if (size < page_size)
		return (page_size * 4);
	if (size < page_size * 10)
		return (page_size * 16);
	else
		return (size + sizeof(t_block) + sizeof(t_allocated) -
				size % page_size + page_size);
}

void		add_block(t_block *block)
{
	size_t		page_size;
	t_block		**list_target;
	t_block		*target;
	size_t		size;

	size = block->size_allocated;

	page_size = getpagesize();
	if (size == page_size * 4)
		list_target = &get_g_mallocs()->tiny;
	else if (size == page_size * 16)
		list_target = &get_g_mallocs()->small;
	else
		list_target = &get_g_mallocs()->large;
	if (*list_target == NULL)
	{
		*list_target = block;
	}
	else
	{
		target = *list_target;
		while (target->next != NULL)
			target = target->next;
		target->next = block;
	}
}

t_block		*create_new_block(size_t block_size)
{
	t_block		*block;

	if ((block = mmap(NULL, block_size, PROT_READ | PROT_WRITE,
					MAP_PRIVATE | MAP_ANONYMOUS, 0, 0)) == MAP_FAILED)
		return NULL;
	block->size_allocated = block_size;
	block->size_used = sizeof(t_block);
	block->next = NULL;
	add_block(block);
	return block;
}

t_block		*find_block_containing_alloc(t_allocated *alloc)
{
	t_block	*block;

	block = get_first_block(return_block_size(alloc->size_queried));
	while (block)
	{
		if ((void*)alloc > (void*)block &&
				(void*)alloc < (void*)block + block->size_allocated)
			return block;
		block = block->next;
	}
	return (NULL);
}
