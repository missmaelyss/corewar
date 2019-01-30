/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_star.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <nbrucker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 19:25:43 by nbrucker          #+#    #+#             */
/*   Updated: 2017/12/02 19:25:43 by nbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_handle_star(t_pf *ft, const char *format, va_list *ag, int *i)
{
	int nbr;

	nbr = va_arg(*ag, int);
	if (format[ft->i - 1] == '.')
	{
		if (nbr >= 0)
			ft->precision = nbr;
		else
			ft->point = 0;
	}
	else
	{
		if (nbr < 0)
		{
			ft->width = nbr * -1;
			ft->minus = 1;
		}
		else
			ft->width = nbr;
	}
	*i = -1;
	ft->i++;
}
