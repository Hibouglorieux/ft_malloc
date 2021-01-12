/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 09:26:49 by nathan            #+#    #+#             */
/*   Updated: 2021/01/12 08:07:08 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	unprotected_free(void *ptr)
{
	t_block		*block;
	t_allocated	*allocated;

	if (!does_pointer_exists(ptr))
		return;
	allocated = user_to_allocated(ptr);
	block = find_block_containing_alloc(allocated);

	//ft_putstr("i must free :");
	//ft_putstr(ft_address_to_hexa(ptr));
	//ft_putendl("");

	//ft_putstr("which has a size of : ");
	//ft_putnbr(allocated->size_queried);
	//ft_putendl("");

	//ft_putstr("block size before: ");
	//ft_putnbr(block->size_used);
	//ft_putendl("");

	block->size_used = block->size_used - allocated->size_queried - sizeof(t_allocated);

	//ft_putstr("block size after: ");
	//ft_putnbr(block->size_used);
	//ft_putendl("");

	remove_alloc(allocated, block);
	if (allocated == get_first_allocated(block))// case in which i need 1rst elem in any case
		create_new_alloc(get_first_allocated(block), 0, NULL, allocated->next);
	if (block->size_used <= sizeof(t_block))
	{
		//ft_putendl("removing block");
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
	size = size - size % 8 + 8;
	block = NULL;
	block_size = return_block_size(size);
	//ft_putstr("i must malloc: ");
	//ft_putnbr(size);
	//ft_putendl("");
	if (get_first_block(block_size) == NULL)
	{
		if (!(block = create_new_block(block_size)))
		{
			//ft_putendl("RETURNING NULL");
			return ((NULL));
		}
		allocated = create_new_alloc(get_first_allocated(block), size, NULL, NULL);
		//ft_putendl("created first block and first alloc");
	}
	else
	{
		allocated = find_space_in_blocks(size);
		//ft_putendl("found space in current blocks");
		if (!allocated)
		{
			//ft_putendl("didnt find space in existing block, creating new allocated");
			if (!(block = create_new_block(block_size)))
			{
				//ft_putendl("RETURNING NULL");
				return ((NULL));
			}
			allocated = create_new_alloc(get_first_allocated(block), size, NULL, NULL);
		}
	}
	//ft_putstr("I allocated: ");
	//ft_putstr(ft_address_to_hexa(allocated_to_user(allocated)));
	//ft_putstr(" with size: ");
	//ft_putnbr(size);
	//ft_putstr(" with parent block ID : ");
	//ft_putstr(ft_address_to_hexa(find_block_containing_alloc(allocated)));
	//ft_putendl("");

	return ((allocated_to_user(allocated)));
}

void	*change_ptr(t_allocated *alloc, size_t size)
{
	void		*user_ptr;

	if (!(user_ptr = unprotected_malloc(size)))
		return (NULL);
	ft_memcpy(user_ptr, allocated_to_user(alloc), ft_min(size, alloc->size_queried));
	unprotected_free(allocated_to_user(alloc));
	return (user_ptr);
}

void	*realloc(void *ptr, size_t size)
{
	t_allocated	*alloc;
	t_block		*block;

	/*if (secure_malloc())
	{
		//ft_putendl("secured FAILED");
		return NULL;
	}
	*/
	size = align_size_for_address(size);
	if (!does_pointer_exists(ptr))
		return (malloc(size));
	//ft_putstr("I must realloc: ");
	//ft_putstr(ft_address_to_hexa(ptr));
	//ft_putstr(" with size: ");
	//ft_putnbr(size);
	//ft_putendl("");
	alloc = user_to_allocated(ptr);
	//ft_putstr("realloc with size: ");
	//ft_putnbr(size);
	//ft_putendl("");
	//ft_putstr("old size: ");
	//ft_putnbr(alloc->size_queried);
	//ft_putendl("");
	secure_malloc();
	block = find_block_containing_alloc(alloc);
	if (size == 0)
		unprotected_free(ptr);
	else if (return_block_size(size) != return_block_size(alloc->size_queried))
	{
		//ft_putendl("must change address");
		return (return_and_release(change_ptr(alloc, size)));
	}
	else if (size < alloc->size_queried)
	{
		//ft_putendl("smaller alloc");
		block->size_used = block->size_used + size - alloc->size_queried;
		alloc->size_queried = size;
	}
	else
	{
		void	*end_address = (void*)alloc + size + sizeof(t_allocated);
		if ((alloc->next == NULL && end_address < (void*)block +
					block->size_allocated) ||
				(end_address < (void*)alloc->next))
		{
			//ft_putendl("bigger in same address: ");
			//ft_putstr("alloc address: ");
			//ft_putstr(ft_address_to_hexa(alloc));
			//ft_putendl("");
			//ft_putstr("alloc->next: ");
			//ft_putstr(ft_address_to_hexa(alloc->next));
			//ft_putendl("");
			//ft_putstr("block: ");
			//ft_putstr(ft_address_to_hexa(block));
			//ft_putstr(" with size: ");
			//ft_putnbr(block->size_allocated);
			//ft_putendl("");
			if (alloc->next == NULL && end_address < (void*)alloc->next)
				ft_putendl("YOO WTF");//TODO ABRUTI DES BOIS
			//ft_putstr("old size used: ");
			//ft_putnbr(block->size_used);
			//ft_putendl("");
			block->size_used = block->size_used + size - alloc->size_queried;
			//ft_putstr("new size: ");
			//ft_putnbr(block->size_used);
			//ft_putendl("");
			alloc->size_queried = size;
		}
		else
		{
			//ft_putendl("bigger in new address");
			return (return_and_release(change_ptr(alloc, size)));
		}
	}
	return return_and_release(ptr);
}
