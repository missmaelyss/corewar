/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 16:15:57 by marnaud           #+#    #+#             */
/*   Updated: 2016/11/18 13:29:23 by marnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	signe(int *n, int *len)
{
	if (*n < 0)
	{
		*n = -*n;
		*len += 1;
	}
}

char			*ft_itoa(int n)
{
	int		tmp;
	int		len;
	char	*str;
	int		s;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = 2;
	s = (n >= 0) ? 0 : 1;
	signe(&n, &len);
	tmp = n;
	while (tmp /= 10)
		len++;
	if ((str = (char*)malloc(sizeof(char) * len)) == NULL)
		return (NULL);
	str[--len] = '\0';
	while (len--)
	{
		str[len] = n % 10 + '0';
		n = n / 10;
	}
	if (s == 1)
		str[0] = '-';
	return (str);
}
