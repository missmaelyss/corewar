/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_lfork.c                                       :+:      :+:    :+:   */
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

void	ft_fork(t_env *env, t_proc *proc)
{
	short	i;

	i = (*(ft_modulo_pc(env, proc->pc + 1)) << 8)
	+ *(ft_modulo_pc(env, proc->pc + 2));
	ft_copy_proc(env, proc, proc->pc + (i % IDX_MOD));
	if ((env->verbose & 4) == 4)
		ft_printf("P %4d | fork %d (%d)\n", proc->index, i,
			((int)(proc->pc - env->arena) + (i % IDX_MOD)));
	ft_move(env, proc, 3);
}

void	ft_lfork(t_env *env, t_proc *proc)
{
	int	i;

	i = ft_get_dir(env, proc->pc + 1, proc->op.name);
	ft_copy_proc(env, proc, proc->pc + (i));
	if ((env->verbose & 4) == 4)
		ft_printf("P %4d | lfork %d (%d)\n", proc->index, i,
			((int)(proc->pc - env->arena) + i));
	ft_move(env, proc, 3);
}
