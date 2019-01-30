/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <nbrucker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 19:25:43 by nbrucker          #+#    #+#             */
/*   Updated: 2017/12/02 19:25:43 by nbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_baselen(t_pf *ft, uintmax_t nbr, int base)
{
	int x;

	if (ft->precision == 0 && ft->point == 1 && nbr == 0)
		return (0);
	if (nbr == 0)
		return (1);
	x = 0;
	while (nbr != 0)
	{
		nbr = nbr / base;
		x++;
	}
	return (x);
}

int		ft_baselen_precision(t_pf *ft, uintmax_t nbr, int base)
{
	if (ft->point == 1 && ft->precision > ft_baselen(ft, nbr, base))
		return (ft->precision);
	return (ft_baselen(ft, nbr, base));
}

void	ft_handle_p(t_pf *ft, va_list *ag)
{
	uintmax_t nbr;

	nbr = va_arg(*ag, unsigned long long);
	ft_handle_width_left(ft, ft_baselen_precision(ft, nbr, 16) + 2);
	ft_putstr_pf(ft, "0x", 2);
	ft_handle_zero(ft, ft_baselen_precision(ft, nbr, 16) + 2);
	ft_putbase(ft, nbr, "0123456789abcdef");
	ft_handle_width_right(ft, ft_baselen_precision(ft, nbr, 16) + 2);
	ft->ready = ft->index;
}
