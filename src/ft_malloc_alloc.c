/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_alloc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 09:49:40 by nathan            #+#    #+#             */
/*   Updated: 2021/02/19 03:50:48 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

t_allocated			*create_new_alloc(t_allocated *new_alloc,
		size_t size_queried, t_allocated *previous, t_allocated *next)
{
	t_block *block;

	new_alloc->size_queried = size_queried;
	block = find_block_containing_alloc(new_alloc);
	if (size_queried != 0)
	{
		block->size_used += align_size_for_address(size_queried)
			+ sizeof(t_allocated);
	}
	new_alloc->next = next;
	if (previous)
		previous->next = new_alloc;
	return (new_alloc);
}

static t_allocated	*find_space_inside_block(t_block *block,
		size_t size_queried, t_allocated *allocated, size_t updated_size)
{
	while (allocated)
	{
		if (allocated->size_queried == 0 && (allocated->next == NULL ||
					(unsigned long)allocated->next - (unsigned long)allocated >=
					align_size_for_address(updated_size)))
			return (create_new_alloc(allocated, size_queried,
						NULL, allocated->next));
		else if (allocated->next == NULL && ((void*)allocated +
					align_size_for_address(allocated->size_queried) +
					sizeof(t_allocated) + updated_size <
					(void*)block + block->size_allocated))
			return (create_new_alloc((void*)allocated + sizeof(t_allocated) +
						align_size_for_address(allocated->size_queried),
						size_queried, allocated, NULL));
		else if ((void*)allocated + sizeof(t_allocated) +
					align_size_for_address(allocated->size_queried) +
					align_size_for_address(updated_size) <=
					(void*)allocated->next)
			return (create_new_alloc((void*)allocated +
						align_size_for_address(allocated->size_queried)
						+ sizeof(t_allocated), size_queried,
						allocated, allocated->next));
			allocated = allocated->next;
	}
	return (allocated);
}

t_allocated			*find_space_in_blocks(size_t size_queried)
{
	t_allocated		*allocated;
	t_block			*block;
	size_t			updated_size;

	allocated = NULL;
	updated_size = size_queried + sizeof(t_allocated);
	block = get_first_block(return_block_size(size_queried));
	while (block)
	{
		if (block->size_allocated - block->size_used < updated_size)
		{
			block = block->next;
			continue ;
		}
		allocated = find_space_inside_block(block, size_queried,
				get_first_allocated(block), size_queried + sizeof(t_allocated));
		if (allocated != NULL)
			break ;
		block = block->next;
	}
	return (allocated);
}
