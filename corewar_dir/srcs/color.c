/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <nbrucker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 19:12:18 by nbrucker          #+#    #+#             */
/*   Updated: 2018/10/15 17:39:21 by qduperon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"
#include "op.h"

void	ft_color(int i)
{
	if (i == 1)
		ft_printf("\x1b[34m");
	else if (i == 2)
		ft_printf("\x1b[32m");
	else if (i == 3)
		ft_printf("\x1b[31m");
	else if (i == 4)
		ft_printf("\x1b[33m");
	else
		ft_printf("\x1b[0m");
}

void	ft_set_color(t_env *env, int start, int size, int color)
{
	int i;
	int x;

	i = 0;
	while (i < size)
	{
		x = (start + i) % MEM_SIZE;
		if (x < 0)
			x = 0;
		env->color[x] = color;
		i++;
	}
	if (env->draw.init == 1)
		ft_drawing(env);
}
