/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_index.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <nbrucker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 19:25:43 by nbrucker          #+#    #+#             */
/*   Updated: 2017/12/02 19:25:43 by nbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_str_index(char **tab, char *str)
{
	int i;

	i = 0;
	while (tab[i])
	{
		if (ft_strcmp(tab[i], str) == 0)
			return (i);
		i++;
	}
	return (-1);
}
