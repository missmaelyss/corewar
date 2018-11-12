/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 12:03:57 by marnaud           #+#    #+#             */
/*   Updated: 2016/11/17 12:22:10 by marnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*tmp;

	if (!(tmp = (void*)malloc(sizeof(size_t) * size)))
		return (0);
	ft_bzero(tmp, size);
	return (tmp);
}
