/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 12:12:02 by marnaud           #+#    #+#             */
/*   Updated: 2016/11/17 15:36:17 by marnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t l)
{
	size_t n;

	n = 0;
	if (l == 0)
		return (0);
	while (s1[n] == s2[n] && s1[n] != '\0' && s2[n] != '\0' && n < l - 1)
		n++;
	return ((unsigned char)s1[n] - (unsigned char)s2[n]);
}
