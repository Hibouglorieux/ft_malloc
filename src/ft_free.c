/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 09:27:46 by nathan            #+#    #+#             */
/*   Updated: 2021/01/11 10:38:34 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include <sys/mman.h>

void	remove_block(t_block *block)
{
	t_block		*target;
	t_mallocs	*mallocs;

	//ft_putstr("removing block with size: ");
	//ft_putnbr(block->size_allocated);
	//ft_putstr(" at address: ");
	//ft_putstr(ft_address_to_hexa(block));
	//ft_putendl("");
	mallocs = get_g_mallocs();
	if (mallocs->tiny == block)
	{
		//ft_putendl("1");
		mallocs->tiny = block->next;
	}
	else if (mallocs->small == block)
	{
		//ft_putendl("2");
		mallocs->small = block->next;
	}
	else if (mallocs->large == block)
	{
		//ft_putendl("3");
		mallocs->large = block->next;
	}
	else
	{
		//ft_putendl("4");
		target = get_first_block(block->size_allocated);
		while (target->next != block)
			target = target->next;
		//ft_putendl("5");
		target->next = block->next;
	}
		//ft_putendl("6");
	munmap(block, block->size_allocated);
		//ft_putendl("7");
}

bool	does_pointer_exists(void *ptr)
{
	t_allocated	*alloc;
	t_allocated	*alloc_received;
	t_block		*block;
	int			i;

	if (!ptr)
	{
		//ft_putendl("ptr is null with free or realloc");
		return (false);
	}
	i = 0;
	alloc_received = user_to_allocated(ptr);
	while (i < 3)
	{
		block = i == 0 ? get_g_mallocs()->tiny : i == 1 ? get_g_mallocs()->small :
			get_g_mallocs()->large;
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
		i++;
	}
	//ft_putendl("call free or realloc with very wrong pointer");
	return (false);
}

void	remove_alloc(t_allocated *removed, t_block *block)
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
		removed->block = NULL;
		removed->next = NULL;
	}
}

void	free(void *ptr)
{
	t_block		*block;
	t_allocated	*allocated;

	if (!does_pointer_exists(ptr))
		return;
	if (secure_malloc())
	{
		ft_putendl("MALLOC DIDNT LOCK");
		return;
	}
	allocated = user_to_allocated(ptr);
	block = allocated->block;

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
	release_secure_malloc();
}
