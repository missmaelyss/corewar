/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursive_factorial.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/09 20:00:00 by marnaud           #+#    #+#             */
/*   Updated: 2016/11/22 13:41:48 by marnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_recursive_factorial(int nb)
{
	if ((nb < 0) || (nb >= 13))
		return (0);
	if (nb == 0)
		return (1);
	if (nb > 1)
	{
		nb = nb * ft_recursive_factorial(nb - 1);
	}
	return (nb);
}
