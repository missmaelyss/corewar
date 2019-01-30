/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <nbrucker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 19:25:43 by nbrucker          #+#    #+#             */
/*   Updated: 2017/12/02 19:25:43 by nbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

void	ft_color(const char *format, t_pf *ft)
{
	if (ft_strncmp(format + ft->i, "{blue}", 6) == 0)
	{
		ft_putstr_pf(ft, "\x1b[34m", 4096);
		ft->i += 5;
	}
	else if (ft_strncmp(format + ft->i, "{red}", 5) == 0)
	{
		ft_putstr_pf(ft, "\x1b[31m", 4096);
		ft->i += 4;
	}
	else if (ft_strncmp(format + ft->i, "{green}", 7) == 0)
	{
		ft_putstr_pf(ft, "\x1b[32m", 4096);
		ft->i += 6;
	}
	else if (ft_strncmp(format + ft->i, "{yellow}", 8) == 0)
	{
		ft_putstr_pf(ft, "\x1b[33m", 4096);
		ft->i += 7;
	}
	else
		ft_color_next(format, ft);
}

void	ft_color_next(const char *format, t_pf *ft)
{
	if (ft_strncmp(format + ft->i, "{black}", 7) == 0)
	{
		ft_putstr_pf(ft, "\x1b[30m", 4096);
		ft->i += 6;
	}
	else if (ft_strncmp(format + ft->i, "{white}", 7) == 0)
	{
		ft_putstr_pf(ft, "\x1b[37m", 4096);
		ft->i += 6;
	}
	else if (ft_strncmp(format + ft->i, "{reset}", 7) == 0)
	{
		ft_putstr_pf(ft, "\x1b[0m", 4096);
		ft->i += 6;
	}
	else if (ft_strncmp(format + ft->i, "{cyan}", 6) == 0)
	{
		ft_putstr_pf(ft, "\x1b[36m", 4096);
		ft->i += 5;
	}
	else
		ft_color_last(format, ft);
}

void	ft_color_last(const char *format, t_pf *ft)
{
	if (ft_strncmp(format + ft->i, "{magenta}", 9) == 0)
	{
		ft_putstr_pf(ft, "\x1b[35m", 4096);
		ft->i += 8;
	}
	else
		ft_putbuf(ft, '{');
}
