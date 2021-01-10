/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_number_to_hexa.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <unkown@noaddress.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 02:02:15 by nathan            #+#    #+#             */
/*   Updated: 2021/01/10 02:20:50 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		reverse_string(char* str)
{
	int i;
	int j;
	unsigned char a;
	size_t len ;
	
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

void		null_into_str(char* str)
{
	str[0] = '0';
	str[1] = 'x';
	str[2] = '0';
	str[3] = '0';
	str[4] = '\0';
}

char*		ft_address_to_hexa(void* address)
{
	static char	str[8] = "";
	unsigned long nb;
	int			i;
	int			tmp;

	if (address == NULL)
	{
		null_into_str(str);
		return str;
	}
	ft_bzero(str, 8);
	nb = (unsigned long)address;
	str[7] = '\0';
	i = 0;
	while (nb && i < 7)
	{
		tmp = 0;
		tmp = nb % 16;
		if (tmp < 10)
			str[i] = tmp + '0';
		else
			str[i] = tmp + 55;
		i++;
		nb /= 16;
	}
	reverse_string(str);
	i = ft_strlen(str);
	str[0] = '0';
	str[1] = 'x';
	str[i] = '\0';
	return str;
}
