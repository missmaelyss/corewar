/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <nbrucker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 19:12:18 by nbrucker          #+#    #+#             */
/*   Updated: 2018/01/30 19:25:43 by nbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		ft_has_number(t_env *env, int number)
{
	int i;

	i = 0;
	if (env->one && env->one->number_set == 1
	&& env->one->live == number)
		i++;
	if (env->two && env->two->number_set == 1
	&& env->two->live == number)
		i++;
	if (env->three && env->three->number_set == 1
	&& env->three->live == number)
		i++;
	if (env->four && env->four->number_set == 1
	&& env->four->live == number)
		i++;
	return (i);
}

void	ft_set_champ_number(t_env *env, t_champ *champ, int n)
{
	int i;

	i = -1;
	while (ft_has_number(env, i) > 0)
		i--;
	champ->number = n;
	if (champ->number_set == 0)
		champ->live = i;
	champ->number_set = 1;
}

void	ft_set_number(t_env *env)
{
	if (env->one)
		ft_set_champ_number(env, env->one, 1);
	if (env->two)
		ft_set_champ_number(env, env->two, 2);
	if (env->three)
		ft_set_champ_number(env, env->three, 3);
	if (env->four)
		ft_set_champ_number(env, env->four, 4);
	ft_create_arena(env);
}
