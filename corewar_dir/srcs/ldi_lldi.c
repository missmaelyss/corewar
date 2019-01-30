/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi_lldi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <nbrucker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 19:12:18 by nbrucker          #+#    #+#             */
/*   Updated: 2018/01/30 19:25:43 by nbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "op.h"
#include "libft.h"

void	ft_load(t_env *env, t_proc *proc, int r1, int r3)
{
	int r2;

	r2 = *(ft_modulo_pc(env, proc->pc + (r1))) << 24;
	r2 += *(ft_modulo_pc(env, proc->pc + (r1) + 1)) << 16;
	r2 += *(ft_modulo_pc(env, proc->pc + (r1) + 2)) << 8;
	r2 += *(ft_modulo_pc(env, proc->pc + (r1) + 3));
	proc->reg[r3] = r2;
	if (proc->op.code == 14)
		ft_set_carry(proc, r3);
	ft_move(env, proc, ft_size(env, proc));
}

void	ft_ldi(t_env *env, t_proc *proc)
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
	if ((*(ft_modulo_pc(env, proc->pc + 1)) & 0xc0) == 0x40)
		r1 = proc->reg[r1];
	if ((*(ft_modulo_pc(env, proc->pc + 1)) & (0xc0 >> 2)) == (0x40 >> 2))
		r2 = proc->reg[r2];
	if ((env->verbose & 4) == 4)
		ft_printf("P %4d | ldi %d %d r%d\n", proc->index, r1, r2, r3 + 1);
	if ((env->verbose & 4) == 4)
		ft_printf("       | -> load from %d + %d = %d (with pc and mod %d)\n",
			r1, r2, r1 + r2, (proc->pc + ((r1 + r2) % IDX_MOD)) - env->arena);
	ft_load(env, proc, (r1 + r2) % IDX_MOD, r3);
}

void	ft_lldi(t_env *env, t_proc *proc)
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
	if ((*(ft_modulo_pc(env, proc->pc + 1)) & 0xc0) == 0x40)
		r1 = proc->reg[r1];
	if ((*(ft_modulo_pc(env, proc->pc + 1)) & (0xc0 >> 2)) == (0x40 >> 2))
		r2 = proc->reg[r2];
	if ((env->verbose & 4) == 4)
		ft_printf("P %4d | lldi %d %d r%d\n", proc->index, r1, r2, r3 + 1);
	if ((env->verbose & 4) == 4)
		ft_printf("       | -> load from %d + %d = %d (with pc %d)\n",
			r1, r2, r1 + r2, (proc->pc + ((r1 + r2))) - env->arena);
	ft_load(env, proc, r1 + r2, r3);
}
