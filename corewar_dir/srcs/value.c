/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <nbrucker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 19:12:18 by nbrucker          #+#    #+#             */
/*   Updated: 2018/03/06 15:42:30 by nbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "op.h"
#include "../../libft/includes/libft.h"

int		ft_get_dir_size(char *str)
{
	if (ft_strcmp(str, "live") == 0)
		return (4);
	else if (ft_strcmp(str, "ld") == 0)
		return (4);
	else if (ft_strcmp(str, "st") == 0)
		return (4);
	else if (ft_strcmp(str, "add") == 0)
		return (4);
	else if (ft_strcmp(str, "sub") == 0)
		return (4);
	else if (ft_strcmp(str, "and") == 0)
		return (4);
	else if (ft_strcmp(str, "or") == 0)
		return (4);
	else if (ft_strcmp(str, "xor") == 0)
		return (4);
	else if (ft_strcmp(str, "lld") == 0)
		return (4);
	else if (ft_strcmp(str, "aff") == 0)
		return (4);
	else
		return (2);
}

int		ft_get_dir(t_env *env, unsigned char *pc, char *str)
{
	int i;

	if (ft_get_dir_size(str) == 4)
	{
		i = *(ft_modulo_pc(env, pc)) << 24;
		i += *(ft_modulo_pc(env, pc + 1)) << 16;
		i += *(ft_modulo_pc(env, pc + 2)) << 8;
		i += *(ft_modulo_pc(env, pc + 3));
	}
	else
	{
		i = *(ft_modulo_pc(env, pc)) << 8;
		i += *(ft_modulo_pc(env, pc + 1));
		i = (short)i;
	}
	return (i);
}

int		ft_get_ind_no_mod(t_env *env, unsigned char *pc, unsigned char *start)
{
	unsigned char	*tmp;
	int				x;

	x = *(ft_modulo_pc(env, pc)) << 8;
	x += *(ft_modulo_pc(env, pc + 1));
	x = (short)x;
	tmp = ft_modulo_pc(env, start + (x));
	x = ft_get_dir(env, tmp, "lived");
	return (x);
}

int		ft_get_ind(t_env *env, unsigned char *pc, unsigned char *start)
{
	unsigned char	*tmp;
	int				x;

	x = *(ft_modulo_pc(env, pc)) << 8;
	x += *(ft_modulo_pc(env, pc + 1));
	x = (short)x;
	tmp = ft_modulo_pc(env, start + (x % IDX_MOD));
	x = ft_get_dir(env, tmp, "live");
	return (x);
}

int		ft_get_reg(t_env *env, unsigned char *pc)
{
	int i;

	i = *(ft_modulo_pc(env, pc)) - 1;
	return (i);
}
