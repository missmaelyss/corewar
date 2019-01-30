/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <nbrucker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 19:12:18 by nbrucker          #+#    #+#             */
/*   Updated: 2019/01/15 18:50:03 by qduperon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "op.h"
#include "libft.h"

void	ft_set_ptr(void (*ptr[16])())
{
	ptr[0] = &ft_live;
	ptr[1] = &ft_ld;
	ptr[2] = &ft_st;
	ptr[3] = &ft_add;
	ptr[4] = &ft_sub;
	ptr[5] = &ft_and;
	ptr[6] = &ft_or;
	ptr[7] = &ft_xor;
	ptr[8] = &ft_zjmp;
	ptr[9] = &ft_ldi;
	ptr[10] = &ft_sti;
	ptr[11] = &ft_fork;
	ptr[12] = &ft_lld;
	ptr[13] = &ft_lldi;
	ptr[14] = &ft_lfork;
	ptr[15] = &ft_aff;
}

void	ft_execute(t_env *env, t_proc *proc)
{
	t_op	op;
	void	(*ptr[16])();

	ft_set_ptr(ptr);
	proc->cycle = 0;
	op = proc->op;
	if (op.name == NULL)
		return ;
	ptr[op.code - 1](env, proc);
	proc->pc = ft_modulo_pc(env, proc->pc);
}

void	ft_set_cycle(t_env *env, t_proc *proc)
{
	t_op	op;

	op = ft_get_op(env, (int)*proc->pc);
	if (op.name == NULL)
	{
		proc->pc = ft_modulo_pc(env, proc->pc + 1);
		proc->cycle = 1;
	}
	else
		proc->cycle = op.cycles;
	proc->op = op;
}

void	ft_inside_play(t_env *env)
{
	if (env->proc->cycle == 0)
		ft_set_cycle(env, env->proc);
	if (env->proc->cycle == 1)
		ft_execute(env, env->proc);
	else
		env->proc->cycle--;
	env->proc->last_live++;
}

void	ft_play(t_env *env)
{
	init(env);
	ft_init_live(env->proc);
	while (glfwGetKey(env->draw.window, GLFW_KEY_ESCAPE) != GLFW_PRESS
	&& glfwWindowShouldClose(env->draw.window) == 0
	&& env->total_cycle < env->dump)
	{
		if (env->cycle >= env->cycle_to_die && ft_check(env) == 1)
			break ;
		if ((env->verbose & 2) == 2)
			ft_printf("It is now cycle %d\n", env->total_cycle + 1);
		env->proc = ft_get_first_proc(env->proc);
		while (env->proc)
		{
			ft_inside_play(env);
			if (env->proc->next == NULL)
				break ;
			env->proc = env->proc->next;
		}
		set_cycle(env);
	}
	ft_end(env);
}
