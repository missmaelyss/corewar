/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <nbrucker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 19:25:43 by nbrucker          #+#    #+#             */
/*   Updated: 2017/12/02 19:25:43 by nbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbrspit(const char *s, char c)
{
	int i;
	int x;

	i = 0;
	x = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			x++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (x);
}

static char	*ft_getword(char *str, char c, int i)
{
	int		x;
	char	*new;

	x = 0;
	while (str[i + x] && str[i + x] != c)
		x++;
	if ((new = (char*)malloc(sizeof(char) * (x + 1))) == NULL)
		return (NULL);
	x = 0;
	while (str[i + x] && str[i + x] != c)
	{
		new[x] = str[i + x];
		x++;
	}
	new[x] = 0;
	return (new);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**tab;
	int		i;
	int		x;

	if (s == NULL)
		return (NULL);
	if ((tab = (char**)malloc(sizeof(char*) * (ft_nbrspit(s, c) + 1))) == NULL)
		return (NULL);
	x = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			if ((tab[x] = ft_getword((char*)s, c, i)) == NULL)
				return (NULL);
			x++;
		}
		while (s[i] && s[i] != c)
			i++;
	}
	tab[x] = 0;
	return (tab);
}
