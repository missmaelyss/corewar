/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <nbrucker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 19:25:43 by nbrucker          #+#    #+#             */
/*   Updated: 2017/12/02 19:25:43 by nbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int		i;
	int		n;
	int		len;

	len = ft_strlen(needle);
	if (len == 0)
		return ((char*)haystack);
	i = 0;
	while (haystack[i])
	{
		n = 0;
		while (haystack[i + n] == needle[n])
		{
			n++;
			if (n == len)
				return ((char*)haystack + i);
		}
		i++;
	}
	return (NULL);
}
