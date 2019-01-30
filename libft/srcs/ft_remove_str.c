/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <nbrucker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 19:25:43 by nbrucker          #+#    #+#             */
/*   Updated: 2017/12/02 19:25:43 by nbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(char **tab, char *str)
{
	int i;
	int x;

	i = 0;
	x = 0;
	while (tab[i])
	{
		if (ft_strcmp(tab[i], str) != 0)
			x++;
		i++;
	}
	return (x);
}

char		**ft_remove_str(char **tab, char *str)
{
	char	**new;
	int		x;
	int		i;

	if ((new = (char**)malloc(sizeof(char*) * (ft_len(tab, str) + 1))) == NULL)
		return (NULL);
	i = 0;
	x = 0;
	while (tab[i])
	{
		if (ft_strcmp(tab[i], str) != 0)
		{
			new[x] = ft_strdup(tab[i]);
			x++;
		}
		i++;
	}
	new[x] = 0;
	return (new);
}
