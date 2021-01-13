/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_variable.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 19:14:00 by nathan            #+#    #+#             */
/*   Updated: 2021/01/13 09:33:47 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static t_mallocs g_mallocs = {NULL, NULL, NULL};

t_mallocs	*get_g_mallocs(void)
{
	return (&g_mallocs);
}
