/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
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

void	ft_aff(t_env *env, t_proc *proc)
{
	int r;
	int size;

	size = ft_size(env, proc);
	if (ft_check_arg(env, proc) == -1)
		return (ft_move(env, proc, size));
	if ((*(ft_modulo_pc(env, proc->pc + 1)) & 0xc0) != 0x40)
		return (ft_move(env, proc, size));
	r = ft_get_reg(env, proc->pc + 2);
	if (r > REG_NUMBER - 1 || r < 0)
		return (ft_move(env, proc, size));
	if (env->a == 1)
		ft_printf("Aff: %c\n", proc->reg[r] % 256);
	ft_move(env, proc, size);
}
