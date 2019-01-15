/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_split_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 16:32:26 by marnaud           #+#    #+#             */
/*   Updated: 2019/01/15 16:35:54 by marnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/op.h"

static int		len_w(char const *s, char *c, int i)
{
	int			len_word;

	len_word = 0;
	while (!(ft_strchr(c, s[i])) && s[i] != '\0')
	{
		len_word++;
		i++;
	}
	if (ft_strchr(c, s[i]) && s[i] != '\0')
		len_word++;
	return (len_word);
}

static int		nb_w(char const *s, char *c)
{
	int			nb_words;

	nb_words = 0;
	while (*s != '\0')
	{
		while (ft_strchr(c, *s) && *s != '\0')
		{
			nb_words++;
			s++;
		}
		if (!(ft_strchr(c, *s)) && *s != '\0')
		{
			nb_words++;
			while (!(ft_strchr(c, *s)) && *s != '\0')
				s++;
			if (ft_strchr(c, *s) && *s != '\0')
				s++;
		}
	}
	return (nb_words);
}

static	void	file(char const *s, char *c, int *n_str, char *tab)
{
	int			n_word;

	n_word = 0;
	while (!(ft_strchr(c, s[*n_str])) && s[*n_str] != '\0')
	{
		tab[n_word] = s[*n_str];
		n_word += 1;
		*n_str += 1;
	}
	if (ft_strchr(c, s[*n_str]))
	{
		tab[n_word] = s[*n_str];
		n_word += 1;
		*n_str += 1;
	}
	tab[n_word] = '\0';
}

char			**ft_strsplit_3(char const *s, char *c)
{
	char		**tab;
	int			n_tab;
	int			n_str;

	if (!s)
		return (0);
	if (!(tab = (char **)malloc(sizeof(char *) * (nb_w(s, c) + 1))))
		return (0);
	n_tab = 0;
	n_str = 0;
	while (n_tab < nb_w(s, c))
	{
		if (!(tab[n_tab] = (char *)malloc(sizeof(char) *
						(len_w(s, c, n_str) + 1))))
			return (0);
		file(s, c, &n_str, tab[n_tab]);
		n_tab++;
	}
	tab[n_tab] = NULL;
	return (tab);
}
