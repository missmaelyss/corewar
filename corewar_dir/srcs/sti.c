/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
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

void	ft_store(t_env *env, t_proc *proc, int r3, int r1)
{
	int size;

	size = ft_size(env, proc);
	*(ft_modulo_pc(env,
	(proc->pc + (r3 % IDX_MOD)) + 0)) = (proc->reg[r1] >> 24) & 0xFF;
	*(ft_modulo_pc(env,
	(proc->pc + (r3 % IDX_MOD)) + 1)) = (proc->reg[r1] >> 16) & 0xFF;
	*(ft_modulo_pc(env,
	(proc->pc + (r3 % IDX_MOD)) + 2)) = (proc->reg[r1] >> 8) & 0xFF;
	*(ft_modulo_pc(env,
	(proc->pc + (r3 % IDX_MOD)) + 3)) = proc->reg[r1] & 0xFF;
	ft_set_color(env, (proc->pc + (r3 % IDX_MOD)) - env->arena, 4, proc->color);
	ft_move(env, proc, size);
}

void	ft_sti(t_env *env, t_proc *proc)
{
	int r1;
	int r2;
	int r3;
	int	i;
	int size;

	size = ft_size(env, proc);
	if (ft_check_arg(env, proc) == -1)
		return (ft_move(env, proc, size));
	i = 2;
	r1 = ft_get_val2(env, proc, &i, 0);
	r2 = ft_get_val2(env, proc, &i, 2);
	r3 = ft_get_val2(env, proc, &i, 4);
	if (i == -42)
		return (ft_move(env, proc, size));
	if ((*(ft_modulo_pc(env, proc->pc + 1)) & (0xc0 >> 4)) == (0x40 >> 4))
		r3 = proc->reg[r3];
	if ((*(ft_modulo_pc(env, proc->pc + 1)) & (0xc0 >> 2)) == (0x40 >> 2))
		r2 = proc->reg[r2];
	if ((env->verbose & 4) == 4)
		ft_printf("P %4d | sti r%d %d %d\n", proc->index, r1 + 1, r2, r3);
	if ((env->verbose & 4) == 4)
		ft_printf("       | -> store to %d + %d = %d (with pc and mod %d)\n",
			r2, r3, r2 + r3, (proc->pc + ((r2 + r3) % IDX_MOD)) - env->arena);
	ft_store(env, proc, r3 + r2, r1);
}
