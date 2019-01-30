/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc.c                                             :+:      :+:    :+:   */
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

t_proc	*ft_get_first_proc(t_proc *proc)
{
	while (proc && proc->previous)
		proc = proc->previous;
	return (proc);
}

t_proc	*ft_malloc_proc(t_env *env, unsigned char *pc, int *i)
{
	t_proc *proc;

	if ((proc = (t_proc*)malloc(sizeof(t_proc))) == NULL)
		ft_error("Malloc error");
	if ((proc->reg = (int*)malloc(sizeof(int) * REG_NUMBER)) == NULL)
		ft_error("Malloc error");
	proc->pc = ft_modulo_pc(env, pc);
	*i = 0;
	return (proc);
}

void	ft_copy_proc(t_env *env, t_proc *dad, unsigned char *pc)
{
	t_proc	*proc;
	t_proc	*first;
	int		i;

	proc = ft_malloc_proc(env, pc, &i);
	while (i < REG_NUMBER)
	{
		proc->reg[i] = dad->reg[i];
		i++;
	}
	proc->last_live = dad->last_live + 1;
	proc->index = env->index;
	env->index++;
	proc->carry = dad->carry;
	proc->color = dad->color;
	proc->cycle = dad->cycle;
	proc->live = dad->live;
	first = ft_get_first_proc(env->proc);
	proc->next = first;
	proc->previous = NULL;
	if (first)
		first->previous = proc;
}

void	ft_new_proc(t_env *env, int number, unsigned char *pc, int color)
{
	t_proc	*proc;
	t_proc	*first;
	int		i;

	proc = ft_malloc_proc(env, pc, &i);
	while (i < REG_NUMBER)
	{
		proc->reg[i] = 0;
		i++;
	}
	env->last_alive = number;
	proc->last_live = 0;
	proc->color = color;
	proc->reg[0] = number;
	proc->index = env->index;
	env->index++;
	proc->carry = 0;
	proc->cycle = 0;
	proc->live = 0;
	first = ft_get_first_proc(env->proc);
	proc->next = first;
	proc->previous = NULL;
	if (first)
		first->previous = proc;
	env->proc = proc;
}

t_proc	*ft_remove_proc(t_env *env, t_proc *proc)
{
	t_proc	*save;

	if ((env->verbose & 8) == 8)
		ft_printf("Process %d hasn\'t lived for %d cycles (CTD %d)\n",
			proc->index, proc->last_live, env->cycle_to_die);
	save = proc->next;
	if (proc->previous)
		proc->previous->next = proc->next;
	if (proc->next)
		proc->next->previous = proc->previous;
	free(proc->reg);
	free(proc);
	return (save);
}
