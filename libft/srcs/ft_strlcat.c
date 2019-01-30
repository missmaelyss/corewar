/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <nbrucker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 19:25:43 by nbrucker          #+#    #+#             */
/*   Updated: 2017/12/02 19:25:43 by nbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t n;

	if (size == 0)
		return (ft_strlen(src));
	i = 0;
	while (dst[i] && i < size)
		i++;
	n = 0;
	while (src[n] && i + n < size - 1)
	{
		dst[i + n] = src[n];
		n++;
	}
	if (i < size)
		dst[i + n] = 0;
	return (i + ft_strlen(src));
}
