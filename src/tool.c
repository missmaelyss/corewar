/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 16:37:56 by marnaud           #+#    #+#             */
/*   Updated: 2019/01/15 16:40:16 by marnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/op.h"

/*
**	void ft_clear_word(char **word)
**	clear a word of '\t' and ','
*/

void		ft_clear_word(char **word)
{
	int		n;

	n = 0;
	while ((*word)[n] != '\0')
	{
		if ((*word)[n] == '\t' || (*word)[n] == SEPARATOR_CHAR)
		{
			while ((*word)[n] != '\0')
			{
				(*word)[n] = (*word)[n + 1];
				n++;
			}
			n = -1;
		}
		n++;
	}
}

int			find_max_len(char *str)
{
	int		i;
	int		max_len;

	i = 0;
	max_len = 0;
	while (g_op_tab[i].name != NULL)
	{
		if (ft_strncmp(g_op_tab[i].name, str,
		ft_strlen(g_op_tab[i].name)) == 0 &&
		(ft_strlen(g_op_tab[i].name) > ft_strlen(g_op_tab[max_len - 1].name)
		|| max_len == 0))
		{
			max_len = i + 1;
		}
		i++;
	}
	return (max_len);
}

char		*add_space_direct_char(char *str)
{
	int		n;
	int		i;
	int		max_len;

	n = 0;
	while (str && str[n] && (str[n] == ' ' || str[n] == '\t'))
		n++;
	max_len = find_max_len(&str[n]);
	n = n + ft_strlen(g_op_tab[max_len - 1].name);
	if (max_len && str[n] == '%')
	{
		i = ft_strlen(str) + 1;
		str = (char *)realloc(str, ft_strlen(str) + 2);
		while (i != n)
		{
			str[i] = str[i - 1];
			i--;
		}
		str[i] = ' ';
	}
	return (str);
}

char		*remove_space_add_char(char *str)
{
	int		n;
	int		virgule;

	n = 0;
	virgule = 0;
	while (str[n] != '\0')
	{
		if (str[n] == ',')
			virgule = 1;
		if ((str[n] == '+' || str[n] == '-') && n > 0
		&& str[n - 1] == ' ' && virgule == 1)
		{
			while (str[n] != '\0')
			{
				str[n - 1] = str[n];
				n++;
			}
			n = -1;
		}
		n++;
	}
	return (str);
}

char		*ft_strrpl(char *dest, const char *src, char a, char b)
{
	int		n;

	n = 0;
	while (src[n] != 0)
	{
		if (src[n] == a)
			dest[n] = b;
		else
			dest[n] = src[n];
		n++;
	}
	dest[n] = 0;
	return (dest);
}
