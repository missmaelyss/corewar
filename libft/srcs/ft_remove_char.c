/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <nbrucker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 19:25:43 by nbrucker          #+#    #+#             */
/*   Updated: 2017/12/02 19:25:43 by nbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(char *str, char c)
{
	int i;
	int x;

	x = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != c)
			x++;
		i++;
	}
	return (x);
}

char		*ft_remove_char(char *str, char c)
{
	int		x;
	int		i;
	char	*new;

	if ((new = (char*)malloc(sizeof(char) * (ft_len(str, c) + 1))) == NULL)
		return (NULL);
	i = 0;
	x = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			new[x] = str[i];
			x++;
		}
		i++;
	}
	new[x] = 0;
	return (new);
}
