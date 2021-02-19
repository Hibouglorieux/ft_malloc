/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 23:11:07 by user42            #+#    #+#             */
/*   Updated: 2021/02/19 00:34:41 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include <sys/mman.h>

void		remove_block(t_block *block)
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
	munmap(block, block->size_allocated);
}
