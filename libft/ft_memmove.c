/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 11:22:08 by marnaud           #+#    #+#             */
/*   Updated: 2016/11/18 15:30:43 by marnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*tmp;

	tmp = ft_strnew(n);
	if (tmp)
	{
		ft_memcpy(tmp, src, n);
		ft_memcpy(dest, tmp, n);
	}
	free(tmp);
	return (dest);
}
