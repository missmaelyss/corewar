/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <nbrucker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 19:25:43 by nbrucker          #+#    #+#             */
/*   Updated: 2017/12/02 19:25:43 by nbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_clear(t_pf *ft)
{
	ft->hash = 0;
	ft->zero = 0;
	ft->minus = 0;
	ft->plus = 0;
	ft->space = 0;
	ft->point = 0;
	ft->h = 0;
	ft->hh = 0;
	ft->l = 0;
	ft->ll = 0;
	ft->j = 0;
	ft->z = 0;
	ft->width = 0;
	ft->precision = 0;
	ft->done = 0;
	ft->neg = 0;
}

void	ft_set_flag(t_flag *flag)
{
	flag[0].c = '#';
	flag[0].f = &ft_set_hash;
	flag[1].c = '0';
	flag[1].f = &ft_set_zero;
	flag[2].c = '-';
	flag[2].f = &ft_set_minus;
	flag[3].c = '+';
	flag[3].f = &ft_set_plus;
	flag[4].c = ' ';
	flag[4].f = &ft_set_space;
	flag[5].c = '.';
	flag[5].f = &ft_set_precision;
	flag[6].c = 'h';
	flag[6].f = &ft_set_h;
	flag[7].c = 'l';
	flag[7].f = &ft_set_l;
	flag[8].c = 'j';
	flag[8].f = &ft_set_j;
	flag[9].c = 'z';
	flag[9].f = &ft_set_z;
	flag[10].c = 0;
	flag[10].f = NULL;
}

void	ft_set_id_next(t_id *id)
{
	id[12].c = 'c';
	id[12].f = &ft_handle_c;
	id[13].c = 'C';
	id[13].f = &ft_handle_uc;
	id[14].c = 'b';
	id[14].f = &ft_handle_b;
	id[15].c = 'B';
	id[15].f = &ft_handle_ub;
	id[16].c = 'n';
	id[16].f = &ft_handle_n;
	id[17].c = 0;
	id[17].f = NULL;
}

void	ft_set_id(t_id *id)
{
	id[0].c = 's';
	id[0].f = &ft_handle_s;
	id[1].c = 'S';
	id[1].f = &ft_handle_us;
	id[2].c = 'p';
	id[2].f = &ft_handle_p;
	id[3].c = 'd';
	id[3].f = &ft_handle_d;
	id[4].c = 'D';
	id[4].f = &ft_handle_ud;
	id[5].c = 'i';
	id[5].f = &ft_handle_d;
	id[6].c = 'o';
	id[6].f = &ft_handle_o;
	id[7].c = 'O';
	id[7].f = &ft_handle_uo;
	id[8].c = 'u';
	id[8].f = &ft_handle_u;
	id[9].c = 'U';
	id[9].f = &ft_handle_uu;
	id[10].c = 'x';
	id[10].f = &ft_handle_x;
	id[11].c = 'X';
	id[11].f = &ft_handle_ux;
	ft_set_id_next(id);
}
