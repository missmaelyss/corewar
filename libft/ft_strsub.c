/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 13:22:56 by marnaud           #+#    #+#             */
/*   Updated: 2016/11/17 11:40:07 by marnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char		*troncon;
	size_t		i;

	if (s == 0)
		return (0);
	if (!(troncon = (char*)malloc(sizeof(char) * (len + 1))))
		return (0);
	i = 0;
	while (len > 0)
	{
		troncon[i] = s[start + i];
		i++;
		len -= 1;
	}
	troncon[i] = 0;
	return (troncon);
}
