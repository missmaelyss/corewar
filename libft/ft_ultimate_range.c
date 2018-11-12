/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultimate_range.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/23 15:05:39 by marnaud           #+#    #+#             */
/*   Updated: 2016/11/22 13:44:01 by marnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_ultimate_range(int **range, int min, int max)
{
	int		i;
	int		*tab;

	if (min >= max)
		return (0);
	i = 0;
	tab = (int*)malloc(sizeof(int) * (max - min + 1));
	while (min < max)
	{
		tab[i] = min;
		min++;
		i++;
	}
	tab[i] = '\0';
	*range = tab;
	return (i);
}
