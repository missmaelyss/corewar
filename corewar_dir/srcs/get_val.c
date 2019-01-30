/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_val.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <nbrucker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 19:12:18 by nbrucker          #+#    #+#             */
/*   Updated: 2018/01/30 19:25:43 by nbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "op.h"

int		ft_get_val_next(t_env *env, t_proc *proc, int *i, int d)
{
	int r;

	r = -1;
	if ((*(ft_modulo_pc(env, proc->pc + 1)) & (0xc0 >> d)) == (0x40 >> d))
	{
		r = ft_get_reg(env, proc->pc + *i);
		if (r > REG_NUMBER - 1 || r < 0)
			*i = -42;
		else
		{
			r = proc->reg[r];
			*i += 1;
		}
	}
	else
		*i = -42;
	return (r);
}

int		ft_get_val(t_env *env, t_proc *proc, int *i, int d)
{
	int r;

	r = -1;
	if (*i == -42)
		return (-1);
	if ((*(ft_modulo_pc(env, proc->pc + 1)) & (0xc0 >> d)) == (0xc0 >> d))
	{
		r = ft_get_ind(env, proc->pc + *i, proc->pc);
		*i += 2;
	}
	else if ((*(ft_modulo_pc(env, proc->pc + 1)) & (0xc0 >> d)) == (0x80 >> d))
	{
		r = ft_get_dir(env, proc->pc + *i, proc->op.name);
		*i += 4;
	}
	else
		return (ft_get_val_next(env, proc, i, d));
	return (r);
}

int		ft_get_val2_next(t_env *env, t_proc *proc, int *i, int d)
{
	int r;

	r = -1;
	if ((*(ft_modulo_pc(env, proc->pc + 1)) & (0xc0 >> d)) == (0x80 >> d))
	{
		r = ft_get_dir(env, proc->pc + *i, proc->op.name);
		*i += 2;
	}
	else
		*i = -42;
	return (r);
}

int		ft_get_val2(t_env *env, t_proc *proc, int *i, int d)
{
	int	r;

	r = -1;
	if (*i == -42)
		return (-1);
	if ((*(ft_modulo_pc(env, proc->pc + 1)) & (0xc0 >> d)) == (0xc0 >> d))
	{
		r = ft_get_ind(env, proc->pc + *i, proc->pc);
		*i += 2;
	}
	else if ((*(ft_modulo_pc(env, proc->pc + 1)) & (0xc0 >> d)) == (0x40 >> d))
	{
		r = ft_get_reg(env, proc->pc + *i);
		if (r > REG_NUMBER - 1 || r < 0)
			*i = -42;
		else
			*i += 1;
	}
	else
		return (ft_get_val2_next(env, proc, i, d));
	return (r);
}
