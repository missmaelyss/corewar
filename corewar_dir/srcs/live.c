/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <nbrucker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 19:12:18 by nbrucker          #+#    #+#             */
/*   Updated: 2018/01/30 19:25:43 by nbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"

void	ft_set_live(t_env *env, int i)
{
	t_champ *champ;

	champ = NULL;
	if (env->one && env->one->live == i)
		champ = env->one;
	else if (env->two && env->two->live == i)
		champ = env->two;
	else if (env->three && env->three->live == i)
		champ = env->three;
	else if (env->four && env->four->live == i)
		champ = env->four;
	if (champ == NULL)
		return ;
	env->last_alive = i;
	if ((env->verbose & 1) == 1)
		ft_printf("Player %d (%s) is said to be alive\n",
			champ->number, champ->name);
}

void	ft_live(t_env *env, t_proc *proc)
{
	int i;

	i = ft_get_dir(env, proc->pc + 1, proc->op.name);
	if ((env->verbose & 4) == 4)
		ft_printf("P %4d | live %d\n", proc->index, i);
	env->live++;
	proc->last_live = -1;
	proc->live = 1;
	ft_set_live(env, i);
	ft_move(env, proc, 5);
}
