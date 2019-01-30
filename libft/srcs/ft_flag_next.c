/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag_next.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <nbrucker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 19:25:43 by nbrucker          #+#    #+#             */
/*   Updated: 2017/12/02 19:25:43 by nbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_set_hash(t_pf *ft, const char *format)
{
	(void)format;
	ft->hash = 1;
}

void	ft_set_zero(t_pf *ft, const char *format)
{
	(void)format;
	ft->zero = 1;
}

void	ft_set_minus(t_pf *ft, const char *format)
{
	(void)format;
	ft->minus = 1;
}

void	ft_set_plus(t_pf *ft, const char *format)
{
	(void)format;
	ft->plus = 1;
}

void	ft_set_space(t_pf *ft, const char *format)
{
	(void)format;
	ft->space = 1;
}
