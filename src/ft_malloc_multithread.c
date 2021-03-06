/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_multithread.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 08:51:42 by nathan            #+#    #+#             */
/*   Updated: 2021/02/18 18:24:57 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "ft_malloc.h"

static pthread_mutex_t g_mutex;

static int	init_mutex(void)
{
	static bool initialized = false;
	int			ret;

	if (initialized)
		return (0);
	initialized = true;
	ret = pthread_mutex_init(&g_mutex, NULL);
	return (ret);
}

int			secure_malloc(void)
{
	int	ret;

	if (init_mutex())
		return (1);
	ret = pthread_mutex_lock(&g_mutex);
	return (ret);
}

int			release_secure_malloc(void)
{
	int	ret;

	if (init_mutex())
		return (1);
	ret = pthread_mutex_unlock(&g_mutex);
	return (ret);
}

void		*return_and_release(void *ptr)
{
	release_secure_malloc();
	return (ptr);
}
