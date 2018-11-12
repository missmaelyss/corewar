/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 14:57:30 by marnaud           #+#    #+#             */
/*   Updated: 2016/11/12 11:40:45 by marnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	char	*sto;
	int		i;

	i = 0;
	sto = (char*)str;
	while (i < (int)n)
	{
		sto[i] = (char)c;
		i++;
	}
	return (str);
}
