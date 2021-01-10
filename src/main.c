/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 21:36:21 by nathan            #+#    #+#             */
/*   Updated: 2021/01/10 01:53:06 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include "libft.h"
#include <stdio.h>

int		main(void)
{
	char* str;
	char* wololo;

	str = malloc(42 * sizeof(char));
	if (!str)
	{
		ft_putstr("error received NULL\n");
		return (1);
	}
	wololo = malloc(42 * sizeof(char));
	if (!wololo)
	{
		ft_putstr("error received NULL for wololo\n");
		return (1);
	}
	ft_bzero(str, 42);
	ft_bzero(wololo, 42);
	ft_strcpy(str, "Hello world !\n");
	ft_strcpy(wololo, "WOLOLOLO !\n");
	ft_putstr(str);
	ft_putstr(wololo);
	free(str);
	return (0);
}
