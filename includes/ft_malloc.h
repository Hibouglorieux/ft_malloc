/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 21:32:54 by nathan            #+#    #+#             */
/*   Updated: 2021/01/13 10:44:57 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H
# include <stdlib.h>
# include "libft.h"

typedef struct			s_block
{
	size_t				size_allocated;
	size_t				size_used;
	struct s_block		*next;
}						t_block;

typedef struct			s_mallocs
{
	t_block				*tiny;
	t_block				*small;
	t_block				*large;
}						t_mallocs;

typedef struct			s_allocated
{
	size_t				size_queried;
	struct s_allocated	*next;
}						t_allocated;

/*
** ft_malloc_print.c
*/
void					show_alloc_mem();

/*
** ft_malloc_variable.c
*/
t_mallocs				*get_g_mallocs();

/*
** ft_malloc_multithread.c
*/
int						secure_malloc(void);
int						release_secure_malloc(void);
void					*return_and_release(void *ptr);

/*
** ft_free.c
*/
void					remove_alloc(t_allocated *removed, t_block *block);
void					remove_block(t_block *block);
bool					does_pointer_exists(void *ptr);
void					free(void *ptr);

/*
** ft_realloc.c
*/
void					*realloc(void *ptr, size_t size);

/*
** ft_malloc_addr.c
*/
t_allocated				*get_first_allocated(t_block *block);
t_allocated				*user_to_allocated(void *ptr);
void					*allocated_to_user(t_allocated *allocated);

/*
** ft_malloc_block.c
*/
t_block					*get_first_block(size_t size);
size_t					return_block_size(size_t size);
void					add_block(t_block *block);
t_block					*create_new_block(size_t block_size);
t_block					*find_block_containing_alloc(t_allocated *alloc);

/*
** ft_malloc_alloc.c
*/

t_allocated				*create_new_alloc(t_allocated *new_alloc,
		size_t size_queried, t_allocated *previous, t_allocated *next);
t_allocated				*find_space_inside_block(t_block *block,
		size_t size_queried);
t_allocated				*find_space_in_blocks(size_t size_queried);

/*
** ft_malloc.c
*/
size_t					align_size_for_address(size_t size);
void					*malloc(size_t size);
void					*calloc(size_t nmemb, size_t size);

/*
** ft_address_to_hexa.c
*/
char					*ft_address_to_hexa(void *address);

#endif
