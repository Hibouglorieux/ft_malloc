/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 21:32:54 by nathan            #+#    #+#             */
/*   Updated: 2021/01/10 19:20:55 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FT_MALLOC__
# define __FT_MALLOC__

#include <stdlib.h>

#define TYNY 1
#define SMALL 4
#define LARGE 10

struct s_block;


typedef struct		s_block
{
	size_t				size_allocated;
	size_t				size_used;
	struct s_block		*next;
}					t_block;

typedef struct		s_mallocs
{
	t_block			*tiny;
	t_block			*small;
	t_block			*large;
}					t_mallocs;

typedef struct		s_allocated
{
	size_t					size_queried;
	struct s_block			*block;
	struct s_allocated		*next;
}					t_allocated;

/*
** ft_malloc_print.c
*/
void	show_alloc_mem();

/*
** ft_malloc_variable.c
*/
t_mallocs	*get_g_mallocs();

void	free(void *ptr);
void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);
t_allocated	*get_first_allocated(t_block *block);
void		*allocated_to_user(t_allocated* allocated);


char*	ft_address_to_hexa(void* address);

#endif
