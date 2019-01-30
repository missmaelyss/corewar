/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 13:21:57 by nbrucker          #+#    #+#             */
/*   Updated: 2018/03/02 13:21:58 by nbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_free_champ(t_champ *champ)
{
	if (champ == NULL)
		return ;
	if (champ->file)
		free(champ->file);
	if (champ->content)
		free(champ->content);
	if (champ->name)
		free(champ->name);
	if (champ->comment)
		free(champ->comment);
	if (champ->code)
		free(champ->code);
	free(champ);
}

void	ft_free(t_env *env)
{
	if (env->arena)
		free(env->arena);
	if (env->color)
		free(env->color);
	ft_free_champ(env->one);
	ft_free_champ(env->two);
	ft_free_champ(env->three);
	ft_free_champ(env->four);
	env->proc = ft_get_first_proc(env->proc);
	while (env->proc)
		env->proc = ft_remove_proc(env, env->proc);
}
