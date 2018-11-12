/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursive_power.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/09 22:10:22 by marnaud           #+#    #+#             */
/*   Updated: 2016/11/22 13:42:21 by marnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_recursive_power(int nb, int power)
{
	if (power > 1)
	{
		nb = nb * ft_recursive_power(nb, power -= 1);
	}
	if (power == 0)
		return (1);
	if (power < 0)
		return (0);
	return (nb);
}
