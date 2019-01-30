/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <nbrucker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 19:25:43 by nbrucker          #+#    #+#             */
/*   Updated: 2017/12/02 19:25:43 by nbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

void	ft_parsing(const char *format, t_flag *flag, t_pf *ft, va_list *ag)
{
	int i;

	i = 0;
	while (flag[i].c != 0 && flag[i].f != NULL)
	{
		if (flag[i].c == format[ft->i])
		{
			flag[i].f(ft, format);
			i = -1;
			ft->i++;
		}
		else if (ft_isdigit(format[ft->i]) == 1 && format[ft->i] != '0')
		{
			ft->width = ft_atoi(format + ft->i);
			ft->i += ft_nbrlen(ft->width);
			i = -1;
		}
		else if (format[ft->i] == '*')
			ft_handle_star(ft, format, ag, &i);
		i++;
	}
	if (ft->minus == 1)
		ft->zero = 0;
	if (ft->plus == 1)
		ft->space = 0;
}

void	ft_parser(const char *format, t_pf *ft, va_list *ag)
{
	t_flag	flag[11];
	t_id	id[18];
	int		i;

	ft->i++;
	ft_set_flag(flag);
	ft_set_id(id);
	ft_clear(ft);
	ft_parsing(format, flag, ft, ag);
	i = 0;
	while (id[i].c != 0 && id[i].f != NULL)
	{
		if (id[i].c == format[ft->i])
		{
			id[i].f(ft, ag);
			i = -1;
			break ;
		}
		i++;
	}
	if (i != -1 && format[ft->i])
		ft_handle_undefined(ft, format[ft->i]);
	if (!format[ft->i])
		ft->i--;
	ft_clear(ft);
}

int		ft_printf(const char *format, ...)
{
	t_pf	ft;
	va_list	ag;

	va_start(ag, format);
	ft.i = 0;
	ft.print = 0;
	ft.index = 0;
	ft.ready = 0;
	while (format[ft.i] && ft.print != -1)
	{
		if (format[ft.i] == '%')
			ft_parser(format, &ft, &ag);
		else if (format[ft.i] == '{')
			ft_color(format, &ft);
		else
			ft_putbuf(&ft, format[ft.i]);
		ft.i++;
	}
	ft_printbuf(&ft);
	return (ft.print);
}
