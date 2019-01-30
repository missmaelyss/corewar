/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <nbrucker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 19:12:18 by nbrucker          #+#    #+#             */
/*   Updated: 2018/01/30 19:25:43 by nbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"

unsigned char	*ft_strnjoin(unsigned char *s1, unsigned int n1,
	unsigned char *s2, unsigned int n2)
{
	unsigned int	i;
	unsigned char	*str;

	if ((str = (unsigned char*)malloc(sizeof(unsigned char)
		* (n1 + n2))) == NULL)
		ft_error("Malloc error");
	i = 0;
	while (i < n1)
	{
		str[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < n2)
	{
		str[i + n1] = s2[i];
		i++;
	}
	return (str);
}

char			*ft_strrev(char *str)
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

char			*ft_itao_base(int value, int size)
{
	unsigned long long	nbr;
	int					i;
	char				*str;
	char				*hex;

	if ((hex = ft_strdup("0123456789abcdef")) == NULL)
		ft_error("Malloc error");
	if ((str = ft_strnew((size * 2) + 1)) == NULL)
		ft_error("Malloc error");
	nbr = value;
	i = 0;
	while (nbr != 0 && i < size * 2)
	{
		str[i] = hex[nbr % 16];
		nbr = nbr / 16;
		i++;
	}
	while (i < size * 2)
	{
		str[i] = '0';
		i++;
	}
	str[i] = 0;
	free(hex);
	return (ft_strrev(str));
}
