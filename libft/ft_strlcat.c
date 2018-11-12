/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 10:53:23 by marnaud           #+#    #+#             */
/*   Updated: 2016/11/17 15:13:32 by marnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dest, const char *src, size_t l)
{
	size_t n;
	size_t i;

	n = 0;
	while (dest[n] != '\0' && n < l)
		n++;
	i = 0;
	while (src[i] != '\0')
		i++;
	if (l >= ft_strlen(dest) + 1)
		dest = ft_strncat(dest, src, l - ft_strlen(dest) - 1);
	return (i + n);
}
