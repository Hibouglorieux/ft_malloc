/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 19:11:28 by nathan            #+#    #+#             */
/*   Updated: 2021/01/10 19:21:53 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include "libft.h"

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
		block = i == 0 ? get_g_mallocs()->tiny : i == 1 ? get_g_mallocs()->small :
			get_g_mallocs()->large;
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
