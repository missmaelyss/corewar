/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 14:10:07 by marnaud           #+#    #+#             */
/*   Updated: 2018/11/13 15:27:15 by marnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int n;
	int s;
	int sto;

	n = 0;
	s = 1;
	sto = 0;
	while (str && (str[n] == ' ' || str[n] == '\t' || str[n] == '\n'
			|| str[n] == '\v' || str[n] == '\f' || str[n] == '\r'))
		n++;
	if (str && str[n] == '-')
	{
		s = -1;
		n++;
	}
	if (str && str[n] == '+' && s == 1)
		n++;
	while (str && str[n] >= '0' && str[n] <= '9')
	{
		sto = sto * 10;
		sto = sto + str[n] - 48;
		n++;
	}
	return (sto * s);
}
