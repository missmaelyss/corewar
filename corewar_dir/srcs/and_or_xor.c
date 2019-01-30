/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or_xor.c                                       :+:      :+:    :+:   */
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

void	ft_and(t_env *env, t_proc *proc)
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
	r1 = ft_get_val(env, proc, &i, 0);
	r2 = ft_get_val(env, proc, &i, 2);
	if (i == -42)
		return (ft_move(env, proc, size));
	r3 = ft_get_reg(env, proc->pc + i);
	if (r3 > REG_NUMBER - 1 || r3 < 0)
		return (ft_move(env, proc, size));
	if ((env->verbose & 4) == 4)
		ft_printf("P %4d | and %d %d r%d\n", proc->index,
			r1, r2, r3 + 1);
	proc->reg[r3] = r1 & r2;
	ft_set_carry(proc, r3);
	ft_move(env, proc, size);
}

void	ft_or(t_env *env, t_proc *proc)
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
	r1 = ft_get_val(env, proc, &i, 0);
	r2 = ft_get_val(env, proc, &i, 2);
	if (i == -42)
		return (ft_move(env, proc, size));
	r3 = ft_get_reg(env, proc->pc + i);
	if (r3 > REG_NUMBER - 1 || r3 < 0)
		return (ft_move(env, proc, size));
	if ((env->verbose & 4) == 4)
		ft_printf("P %4d | or %d %d r%d\n", proc->index,
			r1, r2, r3 + 1);
	proc->reg[r3] = r1 | r2;
	ft_set_carry(proc, r3);
	ft_move(env, proc, size);
}

void	ft_xor(t_env *env, t_proc *proc)
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
	r1 = ft_get_val(env, proc, &i, 0);
	r2 = ft_get_val(env, proc, &i, 2);
	if (i == -42)
		return (ft_move(env, proc, size));
	r3 = ft_get_reg(env, proc->pc + i);
	if (r3 > REG_NUMBER - 1 || r3 < 0)
		return (ft_move(env, proc, size));
	if ((env->verbose & 4) == 4)
		ft_printf("P %4d | xor %d %d r%d\n", proc->index,
			r1, r2, r3 + 1);
	proc->reg[r3] = r1 ^ r2;
	ft_set_carry(proc, r3);
	ft_move(env, proc, size);
}
