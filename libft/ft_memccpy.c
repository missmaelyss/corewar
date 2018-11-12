/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 17:56:10 by marnaud           #+#    #+#             */
/*   Updated: 2016/11/12 11:38:02 by marnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	int		i;
	char	*dest_;
	char	*src_;

	i = 0;
	dest_ = (char*)dest;
	src_ = (char*)src;
	while (i < (int)n)
	{
		dest_[i] = src_[i];
		if (dest_[i] == (char)c)
			return (&dest[i + 1]);
		i++;
	}
	return (0);
}
