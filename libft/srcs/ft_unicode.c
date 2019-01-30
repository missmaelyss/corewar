/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unicode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <nbrucker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 19:25:43 by nbrucker          #+#    #+#             */
/*   Updated: 2017/12/02 19:25:43 by nbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putwchar_pf(t_pf *ft, int c)
{
	if (MB_CUR_MAX == 1 && c >= 128 && c <= 255)
		ft_putbuf(ft, c);
	else if (c <= 0x7F)
		ft_putbuf(ft, c);
	else if (c <= 0x7FF)
	{
		ft_putbuf(ft, 0xC0 | (c >> 6));
		ft_putbuf(ft, 0x80 | (c & 0x3F));
	}
	else if (c <= 0xFFFF)
	{
		ft_putbuf(ft, 0xE0 | (c >> 12));
		ft_putbuf(ft, 0x80 | ((c >> 6) & 0x3F));
		ft_putbuf(ft, 0x80 | (c & 0x3F));
	}
	else if (c <= 0x10FFFF)
	{
		ft_putbuf(ft, 0xF0 | (c >> 18));
		ft_putbuf(ft, 0x80 | ((c >> 12) & 0x3F));
		ft_putbuf(ft, 0x80 | ((c >> 6) & 0x3F));
		ft_putbuf(ft, 0x80 | (c & 0x3F));
	}
}

int		ft_wcharlen(int c)
{
	if (MB_CUR_MAX == 1 && c >= 128 && c <= 255)
		return (1);
	else if (c < 0)
		return (-1);
	else if (c > 0xD7FF && c < 0xE000)
		return (-1);
	else if (c <= 0x7F)
		return (1);
	else if (c <= 0x7FF)
		return (2);
	else if (c <= 0xFFFF)
		return (3);
	else if (c <= 0x10FFFF)
		return (4);
	return (-1);
}

int		ft_check_unicode(wchar_t *str, int len)
{
	int i;
	int x;

	i = 0;
	x = 0;
	if (len == 0)
		return (1);
	while (str[i] && x + ft_wcharlen(str[i]) <= len)
	{
		if (ft_wcharlen(str[i]) == -1 || ft_wcharlen(str[i]) > MB_CUR_MAX)
			return (-1);
		x += ft_wcharlen(str[i]);
		i++;
	}
	if (x < len)
	{
		if (ft_wcharlen(str[i]) == -1 || ft_wcharlen(str[i]) > MB_CUR_MAX)
			return (-1);
	}
	return (1);
}

int		ft_wstrlen(wchar_t *str)
{
	int x;
	int i;

	x = 0;
	i = 0;
	while (str[i])
	{
		x += ft_wcharlen(str[i]);
		i++;
	}
	return (x);
}
