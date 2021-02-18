/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_block.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 09:46:10 by nathan            #+#    #+#             */
/*   Updated: 2021/02/18 23:20:50 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include <sys/mman.h>
#include <sys/resource.h>
#include "unistd.h"

#define MAX_TINY 1024
#define MAX_SMALL 32768

size_t		return_block_size(size_t size)
{
	size_t	page_size;
	size_t	x;

	page_size = getpagesize();
	if (size <= MAX_SMALL)
	{
		x = ((size <= MAX_TINY ? MAX_TINY : MAX_SMALL) +
				sizeof(t_allocated)) * 100 + sizeof(t_block);
		x = x / page_size + ((x % page_size) ? 1 : 0);
	}
	else
	{
		x = size + sizeof(t_block) + sizeof(t_allocated);
		x = x / page_size + ((x % page_size) ? 1 : 0);
	}
	return (page_size * x);
}

t_block		*get_first_block(size_t size)
{
	if (size == return_block_size(MAX_TINY))
		return (get_g_mallocs()->tiny);
	if (size == return_block_size(MAX_SMALL))
		return (get_g_mallocs()->small);
	else
		return (get_g_mallocs()->large);
}

void		add_block(t_block *block)
{
	t_block		**list_target;
	t_block		*target;

	if (block->size_allocated == return_block_size(MAX_TINY))
		list_target = &get_g_mallocs()->tiny;
	else if (block->size_allocated == return_block_size(MAX_SMALL))
		list_target = &get_g_mallocs()->small;
	else
		list_target = &get_g_mallocs()->large;
	if (*list_target == NULL)
		*list_target = block;
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
	t_block			*block;
	struct rlimit	limits;

	getrlimit(RLIMIT_AS, &limits);
	if (limits.rlim_cur < block_size)
		return (NULL);
	if ((block = mmap(NULL, block_size, PROT_READ | PROT_WRITE,
					MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)) == MAP_FAILED)
		return (NULL);
	block->size_allocated = block_size;
	block->size_used = sizeof(t_block);
	block->next = NULL;
	add_block(block);
	return (block);
}

t_block		*find_block_containing_alloc(t_allocated *alloc)
{
	t_block	*block;

	block = get_first_block(return_block_size(alloc->size_queried));
	while (block)
	{
		if ((void*)alloc > (void*)block &&
				(void*)alloc < (void*)block + block->size_allocated)
			return (block);
		block = block->next;
	}
	return (NULL);
}
