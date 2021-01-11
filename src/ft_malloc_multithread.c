/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_multithread.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 08:51:42 by nathan            #+#    #+#             */
/*   Updated: 2021/01/11 10:43:50 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdbool.h>
#include "libft.h"

static pthread_mutex_t g_mutex;

int	init_mutex()
{
	static bool initialized = false;
	int ret;

	if (initialized)
		return (0);
	initialized = true;
	ret = pthread_mutex_init(&g_mutex, NULL);
	return (ret);
}

int	secure_malloc()
{
	int	ret;

	if (init_mutex())
		return (1);
	ret = pthread_mutex_lock(&g_mutex);
	return (ret);
}

int	release_secure_malloc()
{
	int	ret;

	if (init_mutex())
		return (1);
	ret = pthread_mutex_unlock(&g_mutex);
	return (ret);
}

void	*return_and_release(void *ptr)
{
	release_secure_malloc();
	return (ptr);
}

