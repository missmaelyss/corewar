/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr_index.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <nbrucker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 19:25:43 by nbrucker          #+#    #+#             */
/*   Updated: 2017/12/02 19:25:43 by nbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strstr_index(char *big, char *little)
{
	int i;
	int n;
	int len;

	len = ft_strlen(little);
	if (len == 0)
		return (-1);
	i = 0;
	while (big[i])
	{
		n = 0;
		while (big[i + n] == little[n])
		{
			n++;
			if (n == len)
				return (i);
		}
		i++;
	}
	return (-1);
}
