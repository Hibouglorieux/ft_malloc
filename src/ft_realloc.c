/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 09:26:49 by nathan            #+#    #+#             */
/*   Updated: 2021/01/13 10:35:55 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	unprotected_free(void *ptr)
{
	t_block		*block;
	t_allocated	*allocated;

	if (!does_pointer_exists(ptr))
		return ;
	allocated = user_to_allocated(ptr);
	block = find_block_containing_alloc(allocated);
	block->size_used = block->size_used - allocated->size_queried
		- sizeof(t_allocated);
	remove_alloc(allocated, block);
	if (allocated == get_first_allocated(block))
		create_new_alloc(get_first_allocated(block), 0, NULL, allocated->next);
	if (block->size_used <= sizeof(t_block))
	{
		remove_block(block);
	}
}

void	*unprotected_malloc(size_t size)
{
	size_t			block_size;
	t_block			*block;
	t_allocated		*allocated;

	if (size == 0)
		return (NULL);
	size = align_size_for_address(size);
	block_size = return_block_size(size);
	if (get_first_block(block_size) == NULL)
	{
		if (!(block = create_new_block(block_size)))
			return (NULL);
		return ((allocated_to_user(create_new_alloc(
							get_first_allocated(block), size, NULL, NULL))));
	}
	allocated = find_space_in_blocks(size);
	if (allocated)
		return (allocated_to_user(allocated));
	if (!(block = create_new_block(block_size)))
		return (NULL);
	return (allocated_to_user(create_new_alloc(
						get_first_allocated(block), size, NULL, NULL)));
}

void	*change_ptr(t_allocated *alloc, size_t size)
{
	void		*user_ptr;

	if (!(user_ptr = unprotected_malloc(size)))
		return (NULL);
	ft_memcpy(user_ptr, allocated_to_user(alloc),
			ft_min(size, alloc->size_queried));
	unprotected_free(allocated_to_user(alloc));
	return (user_ptr);
}

void	*realloc_part_2(void *ptr, t_block *block, size_t size,
		t_allocated *alloc)
{
	void	*end_address;

	end_address = (void*)alloc + size + sizeof(t_allocated);
	if ((alloc->next == NULL && end_address < (void*)block +
				block->size_allocated) ||
			(end_address < (void*)alloc->next))
	{
		block->size_used = block->size_used + size - alloc->size_queried;
		alloc->size_queried = size;
		return (ptr);
	}
	else
		return (change_ptr(alloc, size));
}

void	*realloc(void *ptr, size_t size)
{
	t_allocated	*alloc;
	t_block		*block;

	secure_malloc();
	size = align_size_for_address(size);
	if (!does_pointer_exists(ptr))
		return (return_and_release(unprotected_malloc(size)));
	alloc = user_to_allocated(ptr);
	block = find_block_containing_alloc(alloc);
	if (size == 0)
		unprotected_free(ptr);
	else if (return_block_size(size) != return_block_size(alloc->size_queried))
	{
		return (return_and_release(change_ptr(alloc, size)));
	}
	else if (size < alloc->size_queried)
	{
		block->size_used = block->size_used + size - alloc->size_queried;
		alloc->size_queried = size;
	}
	else
		return (return_and_release(realloc_part_2(ptr, block, size, alloc)));
	return (return_and_release(ptr));
}
