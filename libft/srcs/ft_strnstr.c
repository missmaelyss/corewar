/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <nbrucker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 19:25:43 by nbrucker          #+#    #+#             */
/*   Updated: 2017/12/02 19:25:43 by nbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t i;
	size_t n;
	size_t l;

	l = ft_strlen(needle);
	if (l == 0)
		return ((char*)haystack);
	i = 0;
	while (haystack[i] && i < len)
	{
		n = 0;
		while (haystack[i + n] == needle[n] && i + n < len)
		{
			n++;
			if (n == l)
				return ((char*)haystack + i);
		}
		i++;
	}
	return (NULL);
}
