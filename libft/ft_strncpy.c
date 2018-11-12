/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 15:04:54 by marnaud           #+#    #+#             */
/*   Updated: 2016/11/12 11:54:29 by marnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	int i;

	i = 0;
	while (src[i] != 0 && i < (int)n)
	{
		dest[i] = src[i];
		i++;
	}
	while (i < (int)n)
	{
		dest[i] = 0;
		i++;
	}
	return (dest);
}
