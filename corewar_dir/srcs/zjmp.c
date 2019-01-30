/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <nbrucker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 19:12:18 by nbrucker          #+#    #+#             */
/*   Updated: 2018/01/30 19:25:43 by nbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"
#include "op.h"

void	ft_zjmp(t_env *env, t_proc *proc)
{
	int x;

	x = ft_get_dir(env, proc->pc + 1, proc->op.name);
	if (proc->carry == 1)
	{
		if ((env->verbose & 4) == 4)
			ft_printf("P %4d | zjmp %d OK\n", proc->index, x);
		proc->pc += x % IDX_MOD;
	}
	else
	{
		if ((env->verbose & 4) == 4)
			ft_printf("P %4d | zjmp %d FAILED\n", proc->index, x);
		ft_move(env, proc, 3);
	}
}
