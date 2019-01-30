/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <nbrucker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 17:28:44 by nbrucker          #+#    #+#             */
/*   Updated: 2019/01/18 18:39:52 by qduperon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char c)
{
	if (c == '\f' || c == '\v' || c == '\n' || c == '\r' || c == '\t'
			|| c == ' ')
		return (1);
	else
		return (0);
}

long long	ft_atoll(const char *s)
{
	size_t		i;
	int			sign;
	long long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (ft_isspace(s[i]))
		i++;
	if (s[i] == '-')
		sign = -1;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (ft_isdigit(s[i]))
	{
		result = result * 10 + s[i] - '0';
		i++;
	}
	return (result * sign);
}
