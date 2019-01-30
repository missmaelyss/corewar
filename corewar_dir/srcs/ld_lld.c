/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld_lld.c                                           :+:      :+:    :+:   */
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

void	ft_lld2(t_env *env, t_proc *proc, int i, int size)
{
	int r;

	if ((*(ft_modulo_pc(env, proc->pc + 1)) & 0xc0) == 0xc0
	&& (*(ft_modulo_pc(env, proc->pc + 1)) & 0x30) == 0x10)
		r = ft_get_reg(env, proc->pc + 4);
	else if ((*(ft_modulo_pc(env, proc->pc + 1)) & 0xc0) == 0x80
	&& (*(ft_modulo_pc(env, proc->pc + 1)) & 0x30) == 0x10)
		r = ft_get_reg(env, proc->pc + 6);
	else
		return (ft_move(env, proc, size));
	if (r > REG_NUMBER - 1 || r < 0)
		return (ft_move(env, proc, size));
	if ((env->verbose & 4) == 4)
		ft_printf("P %4d | lld %d r%d\n", proc->index, i, r + 1);
	proc->reg[r] = i;
	ft_set_carry(proc, r);
	ft_move(env, proc, size);
}

void	ft_lld(t_env *env, t_proc *proc)
{
	int	i;
	int size;

	size = ft_size(env, proc);
	if (ft_check_arg(env, proc) == -1)
		return (ft_move(env, proc, size));
	if ((*(ft_modulo_pc(env, proc->pc + 1)) & 0xc0) == 0xc0)
		i = ft_get_ind_no_mod(env, proc->pc + 2, proc->pc);
	else if ((*(ft_modulo_pc(env, proc->pc + 1)) & 0xc0) == 0x80)
		i = ft_get_dir(env, proc->pc + 2, proc->op.name);
	else
		return (ft_move(env, proc, size));
	ft_lld2(env, proc, i, size);
}

void	ft_ld2(t_env *env, t_proc *proc, int i, int size)
{
	int r;

	if ((*(ft_modulo_pc(env, proc->pc + 1)) & 0xc0) == 0xc0
	&& (*(ft_modulo_pc(env, proc->pc + 1)) & 0x30) == 0x10)
		r = ft_get_reg(env, proc->pc + 4);
	else if ((*(ft_modulo_pc(env, proc->pc + 1)) & 0xc0) == 0x80
	&& (*(ft_modulo_pc(env, proc->pc + 1)) & 0x30) == 0x10)
		r = ft_get_reg(env, proc->pc + 6);
	else
		return (ft_move(env, proc, size));
	if (r > REG_NUMBER - 1 || r < 0)
		return (ft_move(env, proc, size));
	if ((env->verbose & 4) == 4)
		ft_printf("P %4d | ld %d r%d\n", proc->index, i, r + 1);
	proc->reg[r] = i;
	ft_set_carry(proc, r);
	ft_move(env, proc, size);
}

void	ft_ld(t_env *env, t_proc *proc)
{
	int	i;
	int size;

	size = ft_size(env, proc);
	if (ft_check_arg(env, proc) == -1)
		return (ft_move(env, proc, size));
	if ((*(ft_modulo_pc(env, proc->pc + 1)) & 0xc0) == 0xc0)
		i = ft_get_ind(env, proc->pc + 2, proc->pc);
	else if ((*(ft_modulo_pc(env, proc->pc + 1)) & 0xc0) == 0x80)
		i = ft_get_dir(env, proc->pc + 2, proc->op.name);
	else
		return (ft_move(env, proc, size));
	ft_ld2(env, proc, i, size);
}
