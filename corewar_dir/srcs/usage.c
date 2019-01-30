/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 11:12:25 by nbrucker          #+#    #+#             */
/*   Updated: 2018/03/02 11:12:25 by nbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_usage(void)
{
	ft_printf("Usage: ./corewar [-d N -v N -n N] [-a] [-c]");
	ft_printf(" <champion1.cor> <...>\n\n");
	ft_printf("       -a     : Prints output from \"aff\"");
	ft_printf(" (Default is to hide it)\n");
	ft_printf("       -d N   : Dumps memory after N cycles then exits\n");
	ft_printf("       -c     : Colors for dumps\n");
	ft_printf("       -n N   : Set next champion number\n");
	ft_printf("       -v N   : Verbosity levels, can be added together");
	ft_printf(" to enable several\n");
	ft_printf("                - 0 : Show only essentials\n");
	ft_printf("                - 1 : Show lives\n");
	ft_printf("                - 2 : Show cycles\n");
	ft_printf("                - 4 : Show operations (Params are NOT");
	ft_printf(" litteral ...)\n");
	ft_printf("                - 8 : Show deaths\n");
	ft_printf("                - 16 : Show PC movements (Except for jumps)");
	ft_error("");
}
