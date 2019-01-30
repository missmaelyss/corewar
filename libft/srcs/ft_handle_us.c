/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_us.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <nbrucker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 19:25:43 by nbrucker          #+#    #+#             */
/*   Updated: 2017/12/02 19:25:43 by nbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_get_len(int max, wchar_t *str)
{
	int i;
	int x;

	i = 0;
	x = 0;
	while (str[i] && x + ft_wcharlen(str[i]) <= max)
	{
		x += ft_wcharlen(str[i]);
		i++;
	}
	return (x);
}

void	ft_check_null_wstr(t_pf *ft, wchar_t **str, int *len)
{
	if (ft->point == 1 && ft->precision < 1)
	{
		*len = 0;
		return ;
	}
	if (*str == NULL)
		*str = L"(null)";
	if (ft->point == 1 && ft_wstrlen(*str) > ft->precision)
		*len = ft_get_len(ft->precision, *str);
	else
		*len = ft_wstrlen(*str);
}

void	ft_handle_us(t_pf *ft, va_list *ag)
{
	wchar_t		*str;
	int			len;

	str = va_arg(*ag, wchar_t*);
	ft_check_null_wstr(ft, &str, &len);
	if (ft->point == 1 && ft->precision > 0 &&
		ft_wstrlen(str) > ft->precision &&
		ft_check_unicode(str, ft->precision) == -1)
		return (ft_error_printf(ft));
	else if (ft_check_unicode(str, len) == -1)
		return (ft_error_printf(ft));
	ft_handle_width_left(ft, len);
	ft_handle_zero(ft, len);
	if (len > 0)
		ft_putwstr_pf(ft, str, len);
	ft_handle_width_right(ft, len);
	ft->ready = ft->index;
}
