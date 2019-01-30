/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_sub.c                                          :+:      :+:    :+:   */
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

void	ft_add(t_env *env, t_proc *proc)
{
	int r1;
	int r2;
	int r3;
	int size;

	size = ft_size(env, proc);
	if (ft_check_arg(env, proc) == -1)
		return (ft_move(env, proc, size));
	if ((*(ft_modulo_pc(env, proc->pc + 1)) & 0xfc) != 0x54)
		return (ft_move(env, proc, size));
	r1 = ft_get_reg(env, proc->pc + 2);
	r2 = ft_get_reg(env, proc->pc + 3);
	r3 = ft_get_reg(env, proc->pc + 4);
	if (r1 > REG_NUMBER - 1 || r1 < 0)
		return (ft_move(env, proc, size));
	if (r2 > REG_NUMBER - 1 || r2 < 0)
		return (ft_move(env, proc, size));
	if (r3 > REG_NUMBER - 1 || r3 < 0)
		return (ft_move(env, proc, size));
	if ((env->verbose & 4) == 4)
		ft_printf("P %4d | add r%d r%d r%d\n", proc->index,
			r1 + 1, r2 + 1, r3 + 1);
	proc->reg[r3] = proc->reg[r1] + proc->reg[r2];
	ft_set_carry(proc, r3);
	ft_move(env, proc, size);
}

void	ft_sub(t_env *env, t_proc *proc)
{
	int r1;
	int r2;
	int r3;
	int size;

	size = ft_size(env, proc);
	if (ft_check_arg(env, proc) == -1)
		return (ft_move(env, proc, size));
	if ((*(ft_modulo_pc(env, proc->pc + 1)) & 0xfc) != 0x54)
		return (ft_move(env, proc, size));
	r1 = ft_get_reg(env, proc->pc + 2);
	r2 = ft_get_reg(env, proc->pc + 3);
	r3 = ft_get_reg(env, proc->pc + 4);
	if (r1 > REG_NUMBER - 1 || r1 < 0)
		return (ft_move(env, proc, size));
	if (r2 > REG_NUMBER - 1 || r2 < 0)
		return (ft_move(env, proc, size));
	if (r3 > REG_NUMBER - 1 || r3 < 0)
		return (ft_move(env, proc, size));
	if ((env->verbose & 4) == 4)
		ft_printf("P %4d | sub r%d r%d r%d\n", proc->index,
			r1 + 1, r2 + 1, r3 + 1);
	proc->reg[r3] = proc->reg[r1] - proc->reg[r2];
	ft_set_carry(proc, r3);
	ft_move(env, proc, size);
}
