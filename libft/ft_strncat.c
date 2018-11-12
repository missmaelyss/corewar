/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 10:47:17 by marnaud           #+#    #+#             */
/*   Updated: 2016/11/14 11:29:09 by marnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	int		l;
	size_t	i;

	l = 0;
	while (dest[l] != 0)
		l++;
	i = 0;
	while (i < n && src[i])
	{
		dest[l] = src[i];
		l++;
		i++;
	}
	dest[l] = 0;
	return (dest);
}
