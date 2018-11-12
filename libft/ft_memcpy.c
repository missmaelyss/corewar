/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 17:39:06 by marnaud           #+#    #+#             */
/*   Updated: 2016/11/12 11:39:29 by marnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
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
		i++;
	}
	return (dest);
}
