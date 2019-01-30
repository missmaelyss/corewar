/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_buffer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <nbrucker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 19:25:43 by nbrucker          #+#    #+#             */
/*   Updated: 2017/12/02 19:25:43 by nbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putbuf(t_pf *ft, char c)
{
	ft->buf[ft->index] = c;
	ft->index++;
	ft->print++;
	if (ft->index == 4096)
		ft_printbuf(ft);
}

void	ft_printbuf(t_pf *ft)
{
	if (ft->print != -1)
		write(1, ft->buf, ft->index);
	else
		write(1, ft->buf, ft->ready);
	ft->index = 0;
	ft->ready = 0;
}
