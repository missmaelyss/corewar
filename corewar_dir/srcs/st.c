/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
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

void	ft_st2(t_env *env, t_proc *proc, int r1, int r2)
{
	int size;

	size = ft_size(env, proc);
	if ((env->verbose & 4) == 4)
		ft_printf("P %4d | st r%d %d\n", proc->index, r1 + 1, r2);
	if ((*(ft_modulo_pc(env, proc->pc + 1)) & 0x30) == 0x10)
		proc->reg[r2 - 1] = proc->reg[r1];
	else
	{
		*(ft_modulo_pc(env,
		(proc->pc + (r2 % IDX_MOD)) + 0)) = (proc->reg[r1] >> 24) & 0xFF;
		*(ft_modulo_pc(env,
		(proc->pc + (r2 % IDX_MOD)) + 1)) = (proc->reg[r1] >> 16) & 0xFF;
		*(ft_modulo_pc(env,
		(proc->pc + (r2 % IDX_MOD)) + 2)) = (proc->reg[r1] >> 8) & 0xFF;
		*(ft_modulo_pc(env,
		(proc->pc + (r2 % IDX_MOD)) + 3)) = proc->reg[r1] & 0xFF;
		ft_set_color(env, (proc->pc + (r2 % IDX_MOD))
		- env->arena, 4, proc->color);
	}
	ft_move(env, proc, size);
}

void	ft_st(t_env *env, t_proc *proc)
{
	int	r1;
	int	r2;
	int size;

	size = ft_size(env, proc);
	if (ft_check_arg(env, proc) == -1)
		return (ft_move(env, proc, size));
	if ((*(ft_modulo_pc(env, proc->pc + 1)) & 0xc0) == 0x40)
		r1 = ft_get_reg(env, proc->pc + 2);
	else
		return (ft_move(env, proc, size));
	if ((*(ft_modulo_pc(env, proc->pc + 1)) & 0x30) == 0x30)
		r2 = ft_get_dir(env, proc->pc + 3, "fork");
	else if ((*(ft_modulo_pc(env, proc->pc + 1)) & 0x30) == 0x10)
	{
		r2 = ft_get_reg(env, proc->pc + 3) + 1;
		if (r2 > REG_NUMBER || r2 < 1)
			return (ft_move(env, proc, size));
	}
	else
		return (ft_move(env, proc, size));
	if (r1 > REG_NUMBER - 1 || r1 < 0)
		return (ft_move(env, proc, size));
	ft_st2(env, proc, r1, r2);
}
