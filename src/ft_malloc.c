/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 21:32:40 by nathan            #+#    #+#             */
/*   Updated: 2021/01/10 19:52:26 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include "libft.h"
#include <sys/mman.h>
#include <stdio.h>

/*
void *mmap(void *addr, size_t length, int prot, int flags,
		int fd, off_t offset);
int munmap(void *addr, size_t length);
*/

size_t	return_block_size(size_t size)
{
	size_t page_size;

	page_size = getpagesize();
	if (size < page_size)
		return (page_size * 4);
	if (size < page_size * 10)
		return (page_size * 16);
	else
		return (size/* + X*/);
}

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

void	remove_block(t_block *block)
{
	t_block		*target;
	t_mallocs	*mallocs;

	mallocs = get_g_mallocs();
	if (mallocs->tiny == block)
		mallocs->tiny = block->next;
	else if (mallocs->small == block)
		mallocs->small = block->next;
	else if (mallocs->large == block)
		mallocs->large = block->next;
	else
	{
		target = get_first_block(block->size_allocated);
		while (target->next != block)
			target = target->next;
		target->next = block->next;
	}
}

void	add_block(t_block *block)
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

t_allocated	*get_first_allocated(t_block* block)
{
	return (t_allocated*)((void*)block + sizeof(t_block));
}

t_block	*create_new_block(size_t block_size)
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

t_allocated		*create_new_alloc(t_allocated *new_alloc, size_t size_queried, t_allocated *previous,
		t_allocated *next)
{
	new_alloc->size_queried = size_queried;

	new_alloc->block = find_block_containing_alloc(new_alloc);
	if (size_queried != 0)
	{
		ft_putstr("old block size: ");
		ft_putnbr(new_alloc->block->size_used);
		ft_putchar('\n');

		new_alloc->block->size_used += size_queried + sizeof(t_allocated);

		ft_putstr("new block size: ");
		ft_putnbr(new_alloc->block->size_used);
		ft_putchar('\n');
	}
	new_alloc->next = next;
	if (previous)
		previous->next = new_alloc;
	return new_alloc;
}

t_allocated	*find_space_inside_block(t_block *block, size_t size_queried)
{
	t_allocated		*allocated;
	size_t			updated_size;

	allocated = get_first_allocated(block);
	updated_size = size_queried + sizeof(t_allocated);
	while (allocated)
	{
		if (allocated->size_queried == 0 && (void*)allocated->next - (void*)allocated > updated_size)
		{
			ft_putendl("1");
			create_new_alloc(allocated, size_queried, NULL, allocated->next);
			break;
		}
		if (allocated->next == NULL && ((void*)allocated +
					allocated->size_queried + sizeof(t_allocated) + updated_size <
					(void*)block + block->size_allocated))
		{
			ft_putstr("block address: ");
			ft_putstr(ft_address_to_hexa(block));
			ft_putendl("");
			ft_putstr("current alloc address: ");
			ft_putstr(ft_address_to_hexa(allocated));
			ft_putendl("");
			ft_putstr("block_size: ");
			ft_putnbr(block->size_allocated);
			ft_putendl("");

			allocated = create_new_alloc((void*)allocated + sizeof(t_allocated) + allocated->size_queried,
					size_queried, allocated, NULL);
			break;
		}
		else if ((void*)allocated + allocated->size_queried + updated_size +
			sizeof(t_allocated) < (void*)allocated->next)
		{
			ft_putendl("3");
			allocated = create_new_alloc((void*)allocated + allocated->size_queried + sizeof(t_allocated), size_queried, allocated, allocated->next);
			break;
		}
		allocated = allocated->next;
	}
	return (allocated);
}

t_allocated	*find_space_in_blocks(size_t size_queried)
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
			continue;
		}
		allocated = find_space_inside_block(block, size_queried);
		if (allocated != NULL)
			break;
		block = block->next;
	}
	return allocated;
}

void	*allocated_to_user(t_allocated *allocated)
{
	return (void*)((void*)allocated + sizeof(t_allocated));
}

t_allocated	*user_to_allocated(void *ptr)
{
	return (t_allocated*)((void*)ptr - sizeof(t_allocated));
}

void	*malloc(size_t size)
{
	size_t			block_size;
	t_block			*block;
	t_allocated		*allocated;

	if (size == 0)
		return (NULL);
	block = NULL;
	block_size = return_block_size(size);
	ft_putstr("i must malloc: ");
	ft_putnbr(size);
	ft_putendl("");
	if (get_first_block(block_size) == NULL)
	{
		if (!(block = create_new_block(block_size)))
			return (NULL);
		allocated = create_new_alloc(get_first_allocated(block), size, NULL, NULL);
		ft_putendl("created first block and first alloc");
	}
	else
	{
		allocated = find_space_in_blocks(size);
		ft_putendl("found space in current blocks");
		if (!allocated)
		{
			ft_putendl("didnt find space in existing block, creating new allocated");
			if (!(block = create_new_block(block_size)))
				return (NULL);
			allocated = create_new_alloc(get_first_allocated(block), size, NULL, NULL);
		}
	}
	ft_putstr("I allocated: ");
	ft_putstr(ft_address_to_hexa(allocated_to_user(allocated)));
	ft_putstr(" with size: ");
	ft_putnbr(size);
	ft_putstr(" with parent block ID : ");
	ft_putstr(ft_address_to_hexa(allocated->block));
	ft_putendl("");

	return allocated_to_user(allocated);
}

void	remove_alloc(t_allocated *removed, t_block *block)
{
	t_allocated	*tmp;

	tmp = get_first_allocated(block);
	if (tmp == removed)
		create_new_alloc(tmp, 0, NULL, removed->next);
	else
	{
		while (tmp->next != removed)
			tmp = tmp->next;
		tmp->next = removed->next;
		removed->size_queried = 0;
		removed->block = NULL;
		removed->next = NULL;
	}
}

void	free(void *ptr)
{
	t_block		*block;
	t_allocated	*allocated;

	if (!ptr)
		return;
	allocated = user_to_allocated(ptr);
	block = allocated->block;

	ft_putstr("i must free :");
	ft_putstr(ft_address_to_hexa(ptr));
	ft_putendl("");

	ft_putstr("which has a size of : ");
	ft_putnbr(allocated->size_queried);
	ft_putendl("");

	ft_putstr("block size before: ");
	ft_putnbr(block->size_used);
	ft_putendl("");

	block->size_used = block->size_used - allocated->size_queried - sizeof(t_allocated);

	ft_putstr("block size after: ");
	ft_putnbr(block->size_used);
	ft_putendl("");

	remove_alloc(allocated, block);
	if (allocated == get_first_allocated(block))// case in which i need 1rst elem in any case
		create_new_alloc(get_first_allocated(block), 0, NULL, allocated->next);
	if (block->size_used <= sizeof(t_block))
	{
		ft_putendl("removing block");
		remove_block(block);
		munmap(block, block->size_allocated);
	}
}

void	*change_block(t_allocated *alloc, size_t size)
{
	void		*user_ptr;

	user_ptr = malloc(size);
	ft_strncpy(user_ptr, allocated_to_user(alloc), ft_min(size, alloc->size_queried));
	free(allocated_to_user(alloc));
	return (user_ptr);
}

void	*realloc(void *ptr, size_t size)
{
	t_allocated	*alloc;

	if (ptr == NULL)
		return malloc(size);
	ft_putstr("I must realloc: ");
	ft_putstr(ft_address_to_hexa(ptr));
	ft_putstr(" with size: ");
	ft_putnbr(size);
	ft_putendl("");
	alloc = user_to_allocated(ptr);
	if (size == 0)
		free(ptr);
	else if (return_block_size(size) != return_block_size(alloc->size_queried))
		return (change_block(alloc, size));
	else if (size < alloc->size_queried)
	{
		alloc->block->size_used = alloc->block->size_used + size - alloc->size_queried;
		alloc->size_queried = size;
	}
	else
	{
		if (alloc->block->size_used + size - alloc->size_queried < alloc->block->size_allocated &&
				(alloc->next == NULL || (void*)alloc + size + sizeof(t_allocated) < (void*)alloc->next))
		{
			alloc->block->size_used = alloc->block->size_used + size - alloc->size_queried;
			alloc->size_queried = size;
		}
		else
			return (change_block(alloc, size));
	}
	return (ptr);
}
