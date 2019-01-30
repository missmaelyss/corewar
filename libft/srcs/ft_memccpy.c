/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <nbrucker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 19:25:43 by nbrucker          #+#    #+#             */
/*   Updated: 2017/12/02 19:25:43 by nbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	uc;
	char			*a;
	char			*b;

	a = (char*)dst;
	b = (char*)src;
	uc = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		a[i] = b[i];
		if ((unsigned char)b[i] == uc)
			return ((void*)&a[i + 1]);
		i++;
	}
	return (NULL);
}
