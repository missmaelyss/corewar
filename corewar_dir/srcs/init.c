/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <nbrucker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 19:12:18 by nbrucker          #+#    #+#             */
/*   Updated: 2018/03/06 15:42:51 by nbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "op.h"
#include "../../libft/includes/libft.h"

void			ft_init_live(t_proc *proc)
{
	proc = ft_get_first_proc(proc);
	while (proc)
	{
		proc->live = 0;
		proc = proc->next;
	}
}

void			ft_init_env(t_env *env)
{
	ft_op_tab(env);
	env->one = NULL;
	env->two = NULL;
	env->three = NULL;
	env->four = NULL;
	env->nbr_champ = 0;
	env->has_spe = 0;
	env->dump = 2147483647;
	env->cycle_to_die = CYCLE_TO_DIE;
	env->check = 0;
	env->live = 0;
	env->cycle = 0;
	env->total_cycle = 0;
	env->proc = NULL;
	env->index = 1;
	env->verbose = 0;
	env->a = 0;
	env->c = 0;
}

unsigned char	*ft_code(t_env *env, t_champ *c, int i)
{
	unsigned char	*arena;
	int				n;

	n = (MEM_SIZE / env->nbr_champ) * i;
	arena = (unsigned char*)ft_memcpy(env->arena + n, c->code, c->size) - n;
	ft_set_color(env, n, c->size, i + 1);
	return (arena);
}

void			ft_introduce(t_env *env)
{
	ft_putendl("Introducing contestants...");
	if (env->one)
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
		env->one->number, env->one->size, env->one->name,
		env->one->comment);
	if (env->two)
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
		env->two->number, env->two->size, env->two->name,
		env->two->comment);
	if (env->three)
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
		env->three->number, env->three->size, env->three->name,
		env->three->comment);
	if (env->four)
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
		env->four->number, env->four->size, env->four->name,
		env->four->comment);
}

void			ft_create_arena(t_env *env)
{
	int x;

	if (env->one == NULL)
		ft_error("Error: no champ");
	env->arena = (unsigned char*)ft_memalloc(MEM_SIZE);
	env->color = (unsigned char*)ft_memalloc(MEM_SIZE);
	if (env->arena == NULL || env->color == NULL)
		ft_error("Malloc error");
	x = MEM_SIZE / env->nbr_champ;
	env->arena = ft_code(env, env->one, 0);
	ft_new_proc(env, env->one->live, env->arena, 1);
	if (env->two)
		env->arena = ft_code(env, env->two, 1);
	if (env->two)
		ft_new_proc(env, env->two->live, env->arena + x, 2);
	if (env->three)
		env->arena = ft_code(env, env->three, 2);
	if (env->three)
		ft_new_proc(env, env->three->live, env->arena + x * 2, 3);
	if (env->four)
		env->arena = ft_code(env, env->four, 3);
	if (env->four)
		ft_new_proc(env, env->four->live, env->arena + x * 3, 4);
	ft_introduce(env);
	ft_play(env);
}
