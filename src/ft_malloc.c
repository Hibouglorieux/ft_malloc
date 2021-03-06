/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 21:32:40 by nathan            #+#    #+#             */
/*   Updated: 2021/02/19 03:01:27 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include "libft.h"

void	*malloc(size_t size)
{
	size_t			block_size;
	t_block			*block;
	t_allocated		*allocated;

	if (size == 0)
		return (NULL);
	if (secure_malloc())
		return (return_and_release(NULL));
	block_size = return_block_size(size);
	if (get_first_block(block_size) == NULL)
	{
		if (!(block = create_new_block(block_size)))
			return (return_and_release(NULL));
		return (return_and_release(allocated_to_user(create_new_alloc(
							get_first_allocated(block), size, NULL, NULL))));
	}
	allocated = find_space_in_blocks(size);
	if (allocated)
		return (return_and_release(allocated_to_user(allocated)));
	if (!(block = create_new_block(block_size)))
		return (return_and_release(NULL));
	return (return_and_release(allocated_to_user(create_new_alloc(
						get_first_allocated(block), size, NULL, NULL))));
}

void	*calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	ptr = malloc(nmemb * size);
	if (ptr)
		ft_bzero(ptr, nmemb * size);
	return (ptr);
}
