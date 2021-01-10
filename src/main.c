/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 21:36:21 by nathan            #+#    #+#             */
/*   Updated: 2021/01/10 19:28:22 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include "libft.h"
#include <stdio.h>

int		main(void)
{
	int		i = 0;
	char	*ptr[2000];
	char* str;
	char* wololo;

	str = malloc(42 * sizeof(char));
	if (!str)
	{
		ft_putstr("error received NULL\n");
		return (1);
	}
	wololo = malloc(1000 * sizeof(char));
	if (!wololo)
	{
		ft_putstr("error received NULL for wololo\n");
		return (1);
	}
	ft_bzero(str, 42);
	ft_bzero(wololo, 19);
	ft_strcpy(str, "Hello world !\n");
	ft_strcpy(wololo, "WOLOLOLO !\n");
	show_alloc_mem();
	ft_putstr(str);
	ft_putstr(wololo);
	wololo = realloc(wololo, 19);
	show_alloc_mem();
	ft_putstr(wololo);
	free(str);
	str = malloc(1);
	show_alloc_mem();
	free(str);
	free(wololo);
	wololo = malloc(1920 * 1080);
	show_alloc_mem();
	while (i < 2000)
	{
		ptr[i] = malloc(1000);
		if (ptr[i] == NULL)
			ft_putendl("FIN DU MONDE");
		i++;
	}
	i = 0;
	while (i < 2000)
	{
		free(ptr[i]);
		i++;
	}
	free(wololo);
	show_alloc_mem();
	return (0);
}
