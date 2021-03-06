/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 09:26:49 by nathan            #+#    #+#             */
/*   Updated: 2021/02/19 04:00:24 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include "libft.h"

static void	unprotected_free(void *ptr)
{
	t_block		*block;
	t_allocated	*allocated;

	if (!does_pointer_exists(ptr))
		return ;
	allocated = user_to_allocated(ptr);
	block = find_block_containing_alloc(allocated);
	block->size_used = block->size_used -
		align_size_for_address(allocated->size_queried) - sizeof(t_allocated);
	remove_alloc(allocated, block);
	if (get_first_block(block->size_allocated) == get_g_mallocs()->large)
		remove_block(block);
	else
		defragment_blocks(get_first_block(block->size_allocated));
}

static void	*unprotected_malloc(size_t size)
{
	size_t			block_size;
	t_block			*block;
	t_allocated		*allocated;

	if (size == 0)
		return (NULL);
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

static void	*change_ptr(t_allocated *alloc, size_t size)
{
	void		*user_ptr;

	if (!(user_ptr = unprotected_malloc(size)))
		return (NULL);
	ft_memcpy(user_ptr, allocated_to_user(alloc),
			ft_min(size, alloc->size_queried));
	unprotected_free(allocated_to_user(alloc));
	return (user_ptr);
}

static void	*realloc_part_2(void *ptr, t_block *block, size_t size,
		t_allocated *alloc)
{
	void	*end_address;

	end_address = (void*)alloc + size + sizeof(t_allocated);
	if ((alloc->next == NULL && end_address < (void*)block +
				block->size_allocated) ||
			(end_address < (void*)alloc->next))
	{
		block->size_used = block->size_used + align_size_for_address(size) -
			align_size_for_address(alloc->size_queried);
		alloc->size_queried = size;
		return (ptr);
	}
	else
		return (change_ptr(alloc, size));
}

void		*realloc(void *ptr, size_t size)
{
	t_allocated	*alloc;
	t_block		*block;

	secure_malloc();
	if (!ptr)
		return (return_and_release(unprotected_malloc(size)));
	if (!does_pointer_exists(ptr))
		return (return_and_release(NULL));
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
		block->size_used = block->size_used + align_size_for_address(size) -
			align_size_for_address(alloc->size_queried);
		alloc->size_queried = size;
	}
	else
		return (return_and_release(realloc_part_2(ptr, block, size, alloc)));
	return (return_and_release(ptr));
}
