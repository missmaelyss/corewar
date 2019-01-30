/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <nbrucker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 19:25:43 by nbrucker          #+#    #+#             */
/*   Updated: 2017/12/02 19:25:43 by nbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_handle_uc(t_pf *ft, va_list *ag)
{
	wchar_t c;

	c = (wchar_t)va_arg(*ag, wint_t);
	if (ft_wcharlen(c) == -1 || ft_wcharlen(c) > MB_CUR_MAX)
		return (ft_error_printf(ft));
	ft_handle_width_left(ft, ft_wcharlen(c));
	ft_handle_zero(ft, ft_wcharlen(c));
	ft_putwchar_pf(ft, c);
	ft_handle_width_right(ft, ft_wcharlen(c));
	ft->ready = ft->index;
}

void	ft_handle_c(t_pf *ft, va_list *ag)
{
	char c;

	if (ft->l == 1)
		return (ft_handle_uc(ft, ag));
	c = (char)va_arg(*ag, int);
	ft_handle_width_left(ft, 1);
	ft_handle_zero(ft, 1);
	ft_putbuf(ft, c);
	ft_handle_width_right(ft, 1);
	ft->ready = ft->index;
}
