/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 21:32:40 by nathan            #+#    #+#             */
/*   Updated: 2021/01/10 04:05:37 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include "libft.h"
#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>

#define MALLOC_HEADER_SIZE 4
#define MALLOC_HEADER_

/*
void *mmap(void *addr, size_t length, int prot, int flags,
		int fd, off_t offset);
int munmap(void *addr, size_t length);
*/

static t_mallocs g_mallocs = {NULL, NULL, NULL};

void	print_block(t_block *block, char *name)
{
	ft_putstr(name);
	ft_putendl(ft_address_to_hexa((void*)block));
}

void	print_alloc(t_allocated *alloc)
{
	ft_putstr(ft_address_to_hexa((void*)allocated_to_user(alloc)));
	ft_putstr(" - ");
	ft_putstr(ft_address_to_hexa(allocated_to_user((void*)alloc + alloc->size_queried)));
	ft_putstr(" : ");
	ft_putnbr(alloc->size_queried);
	ft_putendl(alloc->size_queried == 1 ? " octet" : " octets");
}

void	show_alloc_mem()
{
	t_allocated *alloc;
	t_block		*block;
	size_t		count;
	char		name[10];
	int			i;

	count = 0;
	i = -1;
	while (++i < 3)
	{
		block = i == 0 ? g_mallocs.tiny : i == 1 ? g_mallocs.small :
			g_mallocs.large;
		ft_strcpy(name, i == 0 ? "TINY: " : i == 1 ? "SMALL: " : "LARGE: " );
		while (block != NULL)
		{
			print_block(block, name);
			if (block && (alloc = get_first_allocated(block)))
				while (alloc)
				{
					print_alloc(alloc);
					count += alloc->size_queried;
					alloc = alloc->next;
				}
			block = block->next;
		}
	}
	ft_putstr("Total : ");
	ft_putnbr(count);
	ft_putendl(count == 1 ? " octet" : " octets");
}

void print_address(void *ptr, char* str)
{
	ft_putstr(str);
	ft_putchar(':');
	ft_putchar(' ');
	ft_putnbr((size_t)ptr);
	ft_putchar('\n');
}

size_t	return_block_size(size_t size)
{
	size_t page_size;

	page_size = getpagesize();
	if (size < page_size)
		return (page_size * 120);
	if (size < page_size * 10)
		return (page_size * 1200);
	else
		return (size/* + X*/);
}

t_block	*get_first_block(size_t size)
{
	size_t page_size;

	page_size = getpagesize();
	if (size == page_size * 120)
		return (g_mallocs.tiny);
	if (size == page_size * 1200)
		return (g_mallocs.small);
	else
		return (g_mallocs.large);
}

void	remove_block(t_block *block)
{
	size_t		page_size;
	t_block		**list_target;
	t_block		*target;
	size_t		size;

	size = block->size_allocated;
	page_size = getpagesize();
	if (size == page_size * 120)
		list_target = &g_mallocs.tiny;
	else if (size == page_size * 1200)
		list_target = &g_mallocs.small;
	else
		list_target = &g_mallocs.large;
	if (*list_target == block)
		*list_target = block->next;
	else
	{
		target = *list_target;
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
	if (size == page_size * 120)
		list_target = &g_mallocs.tiny;
	else if (size == page_size * 1200)
		list_target = &g_mallocs.small;
	else
		list_target = &g_mallocs.large;
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
	return NULL;
}

void		create_new_alloc(t_allocated *new_alloc, size_t size_queried,
		bool is_first)
{
	t_allocated		*last_alloc;

	new_alloc->size_queried = size_queried;
	new_alloc->block = find_block_containing_alloc(new_alloc);
	new_alloc->block->size_used += size_queried + sizeof(t_allocated);
	new_alloc->next = NULL;
	if (!is_first)
	{
		last_alloc = get_last_allocated(new_alloc->block);
		if (last_alloc != NULL)
			last_alloc->next = new_alloc;
	}
}

t_allocated	*find_space_inside_block(size_t size_queried, t_block *block)
{
	t_allocated		*allocated;
	size_t			updated_size;

	allocated = get_first_allocated(block);
	updated_size = size_queried + sizeof(t_allocated);
	while (allocated)
	{
		if (allocated->size_queried == 0)//TODO case where first is needed anyway
			break;
		if ((void*)allocated + allocated->size_queried + updated_size <
				(void*)allocated->next)
		{
			allocated = (t_allocated*)(void*)allocated +
				allocated->size_queried;//TODO insert alloc between
			break;
		}
		allocated = allocated->next;
		if (allocated->next == NULL && ((void*)allocated +
					allocated->size_queried + sizeof(t_allocated) <
					(void*)block + block->size_allocated - updated_size))
			break;
	}
	return (allocated);
}

t_allocated	*find_space_in_blocks(size_t size_queried)
{
	t_allocated		*allocated;
	t_block			*block;
	size_t			updated_size;

	updated_size = size_queried + sizeof(t_allocated);
	block = get_first_block(return_block_size(size_queried));
	while (block)
	{
		if (block->size_allocated - block->size_used < updated_size)
		{
			block = block->next;
			continue;
		}
		allocated = get_first_allocated(block);
		while (allocated->next != NULL)//TODO probleme implementation si maillon entre manquant
			//solution => chercher en faisant des soustractions entre alloc et alloc->next
			//si place inserer le maillon entre
			allocated = allocated->next;
		if ((void*)allocated + allocated->size_queried + sizeof(t_allocated) <
				(void*)block + block->size_allocated - updated_size)
		{
			allocated = (t_allocated*)((void*)allocated +
					allocated->size_queried + sizeof(t_allocated));
			return allocated;
		}
		block = block->next;
	}
	return NULL;
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

	block = NULL;
	block_size = return_block_size(size);
	if (get_first_block(block_size) == NULL || (allocated =
				find_space_in_blocks(size)) == NULL)
	{
		block = create_new_block(block_size);
		allocated = get_first_allocated(block);
	}
	if (allocated)
		create_new_alloc(allocated, size, block == NULL ? false : true);// TODO rework that
	else
	{
		block = create_new_block(block_size);
		if (!block)
			return NULL;
		allocated = get_first_allocated(block);
		create_new_alloc(allocated, size, true);
	}
	return allocated_to_user(allocated);
}

void	free(void *ptr)
{
	t_block		*block;
	t_allocated	*allocated;
	t_allocated	*tmp;
	t_block		*block_tmp;

	allocated = user_to_allocated(ptr);
	block = allocated->block;
	block->size_used -= allocated->size_queried - sizeof(t_allocated);
	if (allocated == get_first_allocated(block) && allocated->next == NULL)
	{
		remove_block(block);
		munmap(block, block->size_allocated);
	}
	if (allocated->next != NULL)
	{
		tmp = get_first_allocated(block);//TODO faiblesse si j'enleve le premier maillon
		if (tmp != allocated)
			while (tmp->next != allocated)
				tmp = tmp->next;
		tmp->next = allocated->next;
	}
	allocated->size_queried = 0;
	allocated->block = NULL;
	allocated->next = NULL;
	if (block->size_used <= sizeof(t_block))
	{
		block_tmp = get_first_block(block->size_allocated);
		if (block_tmp != block)
		{
			while (block_tmp->next != block)
				block_tmp = block_tmp->next;
			block_tmp->next = block->next;
		}
		else
			remove_block(block);
		munmap(block, block->size_allocated);
	}
}

void	*realloc(void *ptr, size_t size)
{
	//ptr = mmap(ptr, size, PROT_NONE, MAP_FIXED)// MAP_FIXED first try
	return ptr;
}
