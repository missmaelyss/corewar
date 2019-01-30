/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduperon <qduperon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 17:07:51 by qduperon          #+#    #+#             */
/*   Updated: 2018/10/16 17:30:33 by qduperon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		champ_is_alive(t_env *env, int i)
{
	t_proc	*proc;

	proc = ft_get_first_proc(env->proc);
	while (proc)
	{
		if (proc->color == i)
			return (1);
		proc = proc->next;
	}
	return (0);
}

char	*champ_name(t_env *env, int i)
{
	if (i == 1)
		return (env->one->name);
	if (i == 2)
		return (env->two->name);
	if (i == 3)
		return (env->three->name);
	if (i == 4)
		return (env->four->name);
	return (NULL);
}
