/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 21:36:21 by nathan            #+#    #+#             */
/*   Updated: 2021/01/12 06:00:21 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

int		main(void)
{
	char	*str;

	for (int i = 0; i < 1026; i++)
	{
		str = malloc(i);
	}
	show_alloc_mem();
	return (0);
}
