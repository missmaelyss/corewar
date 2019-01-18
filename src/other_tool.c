/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_tool.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 16:37:56 by marnaud           #+#    #+#             */
/*   Updated: 2019/01/15 16:40:16 by marnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/op.h"

/*
**	ft_strchrword(char *str, char *word)
**	return the number of time there is the word in the string
*/

int			ft_strchrword(char *str, char *word)
{
	int		words;
	char	*ptr;
	int		n;

	words = 0;
	n = 0;
	if ((ptr = ft_strstr(str, word)) != NULL)
	{
		while (&str[n] != ptr && str[n])
		{
			if (str[n] != ' ' && str[n] != '\t' && &str[n] != ptr && str[n])
			{
				words++;
				while (str[n] != ' ' && str[n] != '\t'
				&& &str[n] != ptr && str[n])
					n++;
			}
			else
				n++;
		}
		words++;
	}
	return (words);
}

/*
**	ft_del_char_ptr(char **tmp)
**	to del a pointer of strings and the strings inside
*/

int			ft_del_char_ptr(char **tmp)
{
	int		i;

	i = 0;
	if (!(tmp[0]))
		return (-1);
	while (tmp[i] != NULL)
	{
		free(tmp[i]);
		i++;
	}
	free(tmp);
	return (1);
}

int			ft_str_is_digit(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!(ft_isdigit(str[i])) && str[i] != '\n' && str[i] != '-')
			return (0);
		i++;
	}
	return (1);
}

int			reverse_endian_int(int a)
{
	char	ret[4];
	char	tmp;

	*(int *)ret = a;
	tmp = ret[0];
	ret[0] = ret[3];
	ret[3] = tmp;
	tmp = ret[1];
	ret[1] = ret[2];
	ret[2] = tmp;
	return (*(int *)ret);
}

short		reverse_endian_short(short a)
{
	char	ret[2];
	char	tmp;

	*(short *)ret = a;
	tmp = ret[0];
	ret[0] = ret[1];
	ret[1] = tmp;
	return (*(short *)ret);
}
