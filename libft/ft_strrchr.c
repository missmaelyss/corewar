/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 12:01:12 by marnaud           #+#    #+#             */
/*   Updated: 2016/11/23 10:27:20 by marnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, char c)
{
	int n;
	int cpt;
	int cpt2;

	n = 0;
	cpt = 0;
	cpt2 = 0;
	if (c == 0)
	{
		while (s[n] != 0)
			n++;
		return ((char *)&s[n]);
	}
	while (s[n] != 0)
	{
		if (s[n] == c)
		{
			cpt2++;
			cpt = n;
		}
		n++;
	}
	if (cpt2)
		return ((char *)&s[cpt]);
	return (0);
}
