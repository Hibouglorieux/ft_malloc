/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 21:32:40 by nathan            #+#    #+#             */
/*   Updated: 2021/01/11 10:49:34 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include <stdio.h>

void	*malloc(size_t size)
{
	size_t			block_size;
	t_block			*block;
	t_allocated		*allocated;

	if (size == 0)
		return (NULL);
	if (secure_malloc())
	{
		ft_putendl("mutex didnt work");
		return (return_and_release(NULL));
	}
	size = size - size % 16 + 16;
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
			return (return_and_release(NULL));
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
				return (return_and_release(NULL));
			}
			allocated = create_new_alloc(get_first_allocated(block), size, NULL, NULL);
		}
	}
	//ft_putstr("I allocated: ");
	//ft_putstr(ft_address_to_hexa(allocated_to_user(allocated)));
	//ft_putstr(" with size: ");
	//ft_putnbr(size);
	//ft_putstr(" with parent block ID : ");
	//ft_putstr(ft_address_to_hexa(allocated->block));
	//ft_putendl("");

	return (return_and_release(allocated_to_user(allocated)));
}

void	*calloc(size_t nmemb, size_t size)
{
	void*	ptr;

	//ft_putendl("I CALLOCED");
	ptr = malloc(nmemb * size);
	if (ptr)
		ft_bzero(ptr, nmemb * size);
	return (ptr);
}
