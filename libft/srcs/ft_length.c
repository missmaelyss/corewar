/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_length.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <nbrucker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 19:25:43 by nbrucker          #+#    #+#             */
/*   Updated: 2017/12/02 19:25:43 by nbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_nbrlen(intmax_t nbr)
{
	int x;

	x = 0;
	if (nbr < 0)
	{
		x++;
		if (nbr < -9)
		{
			x += ft_nbrlen((nbr / 10) * -1);
			x += ft_nbrlen((nbr % 10) * -1);
		}
		else
			x += ft_nbrlen(-nbr);
	}
	else if (nbr > 9)
	{
		x += ft_nbrlen(nbr / 10);
		x += ft_nbrlen(nbr % 10);
	}
	else
		x++;
	return (x);
}
