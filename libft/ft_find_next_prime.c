/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_next_prime.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/09 22:59:27 by marnaud           #+#    #+#             */
/*   Updated: 2016/11/22 14:23:30 by marnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_is_prime_2(int nb)
{
	int a;

	if (nb < 2)
		return (0);
	a = 2;
	while (a < nb)
	{
		if (nb % a == 0)
			return (0);
		a += 1;
	}
	return (nb);
}

int				ft_find_next_prime(int nb)
{
	while (ft_is_prime_2(nb) == 0)
		nb += 1;
	return (ft_is_prime_2(nb));
}
