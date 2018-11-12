/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 12:50:00 by marnaud           #+#    #+#             */
/*   Updated: 2016/11/12 10:11:24 by marnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char *str;

	if (!(str = (char*)malloc(sizeof(char) * ((int)size + 1))))
		return (0);
	while ((int)size >= 0)
	{
		str[(int)size] = 0;
		size--;
	}
	return (str);
}
