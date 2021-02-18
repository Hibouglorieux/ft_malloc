/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_number_to_hexa.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 02:02:15 by nathan            #+#    #+#             */
/*   Updated: 2021/02/18 18:24:01 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include "libft.h"

static void	reverse_string(char *str)
{
	int				i;
	int				j;
	unsigned char	a;
	size_t			len;

	len = ft_strlen(str);
	i = 0;
	j = len - 1;
	while (i < j)
	{
		a = str[i];
		str[i] = str[j];
		str[j] = a;
		i++;
		j--;
	}
}

static char	*null_into_str(char *str)
{
	str[0] = '0';
	str[1] = 'x';
	str[2] = '0';
	str[3] = '0';
	str[4] = '\0';
	return (str);
}

static void	nb_to_string_as_hex(unsigned long nb, char *dest, int len)
{
	int				i;
	unsigned char	tmp;

	i = 0;
	while (nb && i < len)
	{
		tmp = 0;
		tmp = nb % 16;
		if (tmp < 10)
			dest[i] = tmp + '0';
		else
			dest[i] = tmp + 55;
		i++;
		nb /= 16;
	}
	reverse_string(dest);
}

char		*ft_address_to_hexa(void *address)
{
	static char	str[8] = "";

	if (address == NULL)
		return (null_into_str(str));
	ft_bzero(str, 8);
	nb_to_string_as_hex((unsigned long)address, str, 7);
	str[0] = '0';
	str[1] = 'x';
	str[ft_strlen(str)] = '\0';
	return (str);
}
