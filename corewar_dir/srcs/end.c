/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <nbrucker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 19:12:18 by nbrucker          #+#    #+#             */
/*   Updated: 2018/01/30 19:25:43 by nbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"

void	ft_hexdump2(int i)
{
	char	*tmp;

	ft_putstr("0x");
	tmp = ft_itao_base(i, 2);
	ft_putstr(tmp);
	free(tmp);
	ft_putstr(" : ");
}

void	ft_hexdump(t_env *env, unsigned int len)
{
	unsigned int	i;
	char			*hex;

	if ((hex = ft_strdup("0123456789abcdef")) == NULL)
		ft_error("Malloc error");
	i = 0;
	while (i < len)
	{
		if (i != 0)
			ft_putchar(' ');
		if (i != 0 && i % 64 == 0)
			ft_putchar('\n');
		if (i % 64 == 0)
			ft_hexdump2(i);
		if (env->c == 1)
			ft_color(env->color[i]);
		ft_putchar(hex[env->arena[i] / 16]);
		ft_putchar(hex[env->arena[i] % 16]);
		if (env->c == 1)
			ft_printf("\x1b[0m");
		i++;
	}
	free(hex);
	ft_putstr(" \n");
}

void	ft_win(t_env *env)
{
	t_champ *champ;

	champ = NULL;
	if (env->one && env->one->live == env->last_alive)
		champ = env->one;
	else if (env->two && env->two->live == env->last_alive)
		champ = env->two;
	else if (env->three && env->three->live == env->last_alive)
		champ = env->three;
	else if (env->four && env->four->live == env->last_alive)
		champ = env->four;
	if (champ == NULL)
		return ;
	ft_printf("Contestant %d, \"%s\", has won !\n", champ->number,
		champ->name);
}
