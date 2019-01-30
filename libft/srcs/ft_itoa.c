/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <nbrucker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 19:25:43 by nbrucker          #+#    #+#             */
/*   Updated: 2017/12/02 19:25:43 by nbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbrlen(long long n)
{
	int i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		i++;
		n *= -1;
	}
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static char	*ft_strrev(char *str)
{
	int		i;
	int		j;
	char	tmp;

	i = 0;
	j = ft_strlen(str) - 1;
	while (j > i)
	{
		tmp = str[i];
		str[i] = str[j];
		str[j] = tmp;
		i++;
		j--;
	}
	return (str);
}

char		*ft_itoa(int n)
{
	long long	nbr;
	char		*str;
	int			i;
	int			neg;

	nbr = (long long)n;
	neg = 0;
	if ((str = (char*)malloc(sizeof(char) * (ft_nbrlen(nbr) + 1))) == NULL)
		return (NULL);
	i = 0;
	if (nbr < 0)
	{
		neg = 1;
		nbr *= -1;
	}
	while (nbr != 0 || i == 0)
	{
		str[i] = (nbr % 10) + 48;
		nbr /= 10;
		i++;
	}
	if (neg == 1)
		str[i++] = '-';
	str[i] = 0;
	return (ft_strrev(str));
}
