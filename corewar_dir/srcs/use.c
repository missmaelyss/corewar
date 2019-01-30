/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use.c                                              :+:      :+:    :+:   */
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

unsigned char	*ft_modulo_pc(t_env *env, unsigned char *pc)
{
	int new_pc;

	new_pc = pc - env->arena;
	new_pc = new_pc % MEM_SIZE;
	if (new_pc < 0)
		new_pc = MEM_SIZE + new_pc;
	return (env->arena + new_pc);
}

int				ft_check_arg(t_env *env, t_proc *proc)
{
	int		i;
	t_op	op;
	int		code;
	int		d;

	op = proc->op;
	i = 0;
	code = *(ft_modulo_pc(env, proc->pc + 1));
	while (i < op.params)
	{
		d = (3 - i) * 2;
		if ((op.types[i] & 1) == 1 && (code & (3 << d)) == (1 << d))
			i++;
		else if ((op.types[i] & 2) == 2 && (code & (3 << d)) == (2 << d))
			i++;
		else if ((op.types[i] & 4) == 4 && (code & (3 << d)) == (3 << d))
			i++;
		else
			return (-1);
	}
	return (1);
}

int				ft_size(t_env *env, t_proc *proc)
{
	int		i;
	t_op	op;
	int		size;

	op = proc->op;
	i = 0;
	size = 2;
	while (i < op.params)
	{
		if ((*(ft_modulo_pc(env, proc->pc + 1)) & (0xc0 >> (i * 2)))
			== (0xc0 >> (i * 2)))
			size += 2;
		else if ((*(ft_modulo_pc(env, proc->pc + 1)) & (0xc0 >> (i * 2)))
			== (0x80 >> (i * 2)))
			size += ft_get_dir_size(op.name);
		else if ((*(ft_modulo_pc(env, proc->pc + 1)) & (0xc0 >> (i * 2)))
			== (0x40 >> (i * 2)))
			size += 1;
		i++;
	}
	return (size);
}

void			ft_move(t_env *env, t_proc *proc, int i)
{
	unsigned char	*start;
	int				j;

	start = proc->pc;
	proc->pc = ft_modulo_pc(env, proc->pc + i);
	if ((env->verbose & 16) == 16)
		ft_printf("ADV %d (%.4p -> %.4p) ", i, (void*)(start - env->arena),
		(void*)(start - env->arena + i));
	j = 0;
	while ((env->verbose & 16) == 16 && j < i)
	{
		ft_printf("%.2x ", *(ft_modulo_pc(env, start + j)));
		j++;
	}
	if ((env->verbose & 16) == 16)
		ft_putchar('\n');
}

void			ft_set_carry(t_proc *proc, int r)
{
	if (proc->reg[r] == 0)
		proc->carry = 1;
	else
		proc->carry = 0;
}
