/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_n.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <nbrucker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 19:25:43 by nbrucker          #+#    #+#             */
/*   Updated: 2017/12/02 19:25:43 by nbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_error_printf(t_pf *ft)
{
	ft->print = -1;
}

void	ft_handle_n(t_pf *ft, va_list *ag)
{
	void *ptr;

	ptr = va_arg(*ag, void*);
	if (ptr == NULL)
		return (ft_error_printf(ft));
	if (ft->z == 1)
		*(size_t*)ptr = (size_t)ft->print;
	else if (ft->j == 1)
		*(intmax_t*)ptr = (intmax_t)ft->print;
	else if (ft->ll == 1)
		*(long long*)ptr = (long long)ft->print;
	else if (ft->l == 1)
		*(long*)ptr = (long)ft->print;
	else if (ft->h == 1)
		*(short*)ptr = (short)ft->print;
	else if (ft->hh == 1)
		*(char*)ptr = (char)ft->print;
	else
		*(int*)ptr = (int)ft->print;
}
