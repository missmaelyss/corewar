/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
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

t_proc	*ft_get_alive(t_env *env, t_proc *proc)
{
	while (proc)
	{
		if (proc->last_live < env->cycle_to_die)
			return (proc);
		proc = proc->next;
	}
	return (NULL);
}

t_proc	*ft_check_live(t_env *env, t_proc *proc)
{
	t_proc	*save;

	proc = ft_get_first_proc(proc);
	save = ft_get_alive(env, proc);
	while (proc)
	{
		if (proc->last_live >= env->cycle_to_die)
			proc = ft_remove_proc(env, proc);
		else
			proc = proc->next;
	}
	return (ft_get_first_proc(save));
}

int		ft_check(t_env *env)
{
	env->proc = ft_check_live(env, env->proc);
	ft_init_live(env->proc);
	if (env->live >= NBR_LIVE)
	{
		env->cycle_to_die -= CYCLE_DELTA;
		if ((env->verbose & 2) == 2)
			ft_printf("Cycle to die is now %d\n", env->cycle_to_die);
		env->check = 0;
	}
	else
		env->check++;
	if (env->check >= MAX_CHECKS)
	{
		env->cycle_to_die -= CYCLE_DELTA;
		if ((env->verbose & 2) == 2)
			ft_printf("Cycle to die is now %d\n", env->cycle_to_die);
		env->check = 0;
	}
	env->live = 0;
	env->cycle = 0;
	if (env->proc == NULL)
		return (1);
	return (0);
}
