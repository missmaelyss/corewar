/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 15:33:10 by marnaud           #+#    #+#             */
/*   Updated: 2016/11/12 11:44:39 by marnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dest, const char *src)
{
	int n;
	int i;

	n = 0;
	while (dest[n] != 0)
		n++;
	i = 0;
	while (src[i] != 0)
	{
		dest[n] = src[i];
		n++;
		i++;
	}
	dest[n] = 0;
	return (dest);
}
