/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <nbrucker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 19:12:18 by nbrucker          #+#    #+#             */
/*   Updated: 2018/03/06 15:41:45 by nbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "../../libft/includes/libft.h"

int		ft_is_number(char *str)
{
	char *tmp;

	tmp = ft_itoa(ft_atoi(str));
	if (tmp == NULL)
		ft_error("Malloc error");
	if (ft_strcmp(tmp, str) != 0)
	{
		free(tmp);
		return (0);
	}
	free(tmp);
	return (1);
}

void	ft_get_dump(t_env *env, int *i, int argc, char **argv)
{
	if (*i + 1 >= argc)
		ft_error("Error: -d nbr_cycles");
	if (ft_is_number(argv[*i + 1]) == 0)
		ft_error("Error: -d nbr_cycles");
	env->dump = ft_atoi(argv[*i + 1]);
	*i += 1;
}

void	ft_get_n(t_env *env, int *i, int argc, char **argv)
{
	if (*i + 1 >= argc)
		ft_error("Error: -n number");
	if (ft_is_number(argv[*i + 1]) == 0)
		ft_error("Error: -n number");
	env->has_spe = 1;
	env->spe_number = ft_atoi(argv[*i + 1]);
	*i += 1;
}

void	ft_get_v(t_env *env, int *i, int argc, char **argv)
{
	if (*i + 1 >= argc)
		ft_error("Error: -v number");
	if (ft_is_number(argv[*i + 1]) == 0)
		ft_error("Error: -v number");
	env->verbose = ft_atoi(argv[*i + 1]);
	*i += 1;
}
