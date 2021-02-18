/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 19:11:28 by nathan            #+#    #+#             */
/*   Updated: 2021/02/18 18:21:36 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include "libft.h"

static void		print_alloc(t_allocated *alloc)
{
	if (alloc->size_queried != 0)
	{
		ft_putstr(ft_address_to_hexa((void*)allocated_to_user(alloc)));
		ft_putstr(" - ");
		ft_putstr(ft_address_to_hexa(allocated_to_user((void*)alloc +
						alloc->size_queried)));
		ft_putstr(" : ");
		ft_putnbr(alloc->size_queried);
		ft_putendl(alloc->size_queried == 1 ? " octet" : " octets");
	}
}

static void		print_block_and_allocs(t_block *block, char *name,
		size_t *count)
{
	t_allocated	*alloc;

	ft_putstr(name);
	ft_putendl(ft_address_to_hexa((void*)block));
	alloc = get_first_allocated(block);
	while (alloc)
	{
		print_alloc(alloc);
		*count += alloc->size_queried;
		alloc = alloc->next;
	}
}

static t_block	*initialize_block_and_name(char *dest, int i)
{
	t_block	*block;

	if (i == 0)
	{
		ft_strcpy(dest, "TINY: ");
		block = get_g_mallocs()->tiny;
	}
	else if (i == 1)
	{
		ft_strcpy(dest, "SMALL: ");
		block = get_g_mallocs()->small;
	}
	else
	{
		ft_strcpy(dest, "LARGE: ");
		block = get_g_mallocs()->large;
	}
	return (block);
}

static void		print_total(size_t count)
{
	ft_putstr("Total : ");
	ft_putnbr(count);
	ft_putendl(count == 1 ? " octet" : " octets");
}

void			show_alloc_mem(void)
{
	t_block		*block;
	size_t		count;
	char		name[10];
	int			i;

	secure_malloc();
	count = 0;
	i = -1;
	while (++i < 3)
	{
		block = initialize_block_and_name(name, i);
		while (block != NULL)
		{
			print_block_and_allocs(block, name, &count);
			block = block->next;
		}
	}
	print_total(count);
	release_secure_malloc();
}
