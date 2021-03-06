/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 19:00:10 by nallani           #+#    #+#             */
/*   Updated: 2018/10/14 23:02:25 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strcat(char *s1, char const *s2)
{
	int		i;
	int		j;

	i = 0;
	j = -1;
	while (s1[i])
		i++;
	while (s2[++j])
		s1[i++] = s2[j];
	s1[i] = '\0';
	return (s1);
}
