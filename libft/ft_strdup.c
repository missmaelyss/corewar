/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 14:17:03 by marnaud           #+#    #+#             */
/*   Updated: 2017/01/24 14:19:41 by marnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	size_t		i;
	char		*str;

	if (!((str = (char*)malloc(sizeof(*str) * (ft_strlen(src) + 1)))))
		return (0);
	i = 0;
	while (src[i] != 0)
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
