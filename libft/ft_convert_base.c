/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/24 23:28:35 by marnaud           #+#    #+#             */
/*   Updated: 2017/01/24 15:22:08 by marnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		sous_fonction_nulle(int *m, int *pw, char *base_to)
{
	while (*m / (int)ft_strlen(base_to) > 0)
	{
		*m = *m / ((int)ft_strlen(base_to));
		*pw += 1;
	}
}

static char		*ft_convert_nb_s(int nb, char *base_to)
{
	char	*nbr;
	int		pw;
	int		n;
	int		m;

	pw = 0;
	m = nb;
	sous_fonction_nulle(&m, &pw, base_to);
	n = 0;
	nbr = (char*)malloc(sizeof(char) * (pw + 1 + 1));
	while (pw >= 0)
	{
		if (nb - m * (ft_recursive_power(ft_strlen(base_to), pw)) < 0)
			m = 0;
		nbr[n] = base_to[m];
		nb -= m * (ft_recursive_power(ft_strlen(base_to), pw));
		m = nb;
		n += 1;
		pw -= 1;
		while (m >= ((int)ft_strlen(base_to)))
			m = m / (ft_strlen(base_to));
	}
	nbr[n] = 0;
	return (nbr);
}

char			*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	int n;
	int m;
	int nb;
	int pw;

	n = ft_strlen(nbr) - 1;
	m = 0;
	nb = 0;
	pw = 0;
	while (base_from[m] && n >= 0)
	{
		if (base_from[m] == nbr[n])
		{
			nb = nb + ft_recursive_power(ft_strlen(base_from), pw) * m;
			n--;
			pw++;
			m = -1;
		}
		m++;
	}
	return (ft_convert_nb_s(nb, base_to));
}
