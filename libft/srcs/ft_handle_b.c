/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_b.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <nbrucker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 19:25:43 by nbrucker          #+#    #+#             */
/*   Updated: 2017/12/02 19:25:43 by nbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_handle_ub(t_pf *ft, va_list *ag)
{
	ft->ll = 0;
	ft->h = 0;
	ft->hh = 0;
	ft->j = 0;
	ft->z = 0;
	ft->l = 1;
	ft_handle_b(ft, ag);
}

void	ft_handle_b(t_pf *ft, va_list *ag)
{
	uintmax_t nbr;

	nbr = ft_get_uint(ft, ag);
	ft_remove_zero(ft);
	ft_handle_width_left(ft, ft_baselen_precision(ft, nbr, 2));
	ft_handle_zero(ft, ft_baselen_precision(ft, nbr, 2));
	ft_putbase(ft, nbr, "01");
	ft_handle_width_right(ft, ft_baselen_precision(ft, nbr, 2));
	ft->ready = ft->index;
}
