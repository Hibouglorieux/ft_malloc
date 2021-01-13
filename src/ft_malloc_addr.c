/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_addr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 09:30:02 by nathan            #+#    #+#             */
/*   Updated: 2021/01/13 07:19:54 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

t_allocated	*get_first_allocated(t_block *block)
{
	return (t_allocated*)((void*)block + sizeof(t_block));
}

t_allocated	*user_to_allocated(void *ptr)
{
	return (t_allocated*)((void*)ptr - sizeof(t_allocated));
}

void		*allocated_to_user(t_allocated *allocated)
{
	return (void*)((void*)allocated + sizeof(t_allocated));
}
