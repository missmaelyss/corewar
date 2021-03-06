/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_label.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaud <marnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 16:37:56 by marnaud           #+#    #+#             */
/*   Updated: 2019/01/22 13:27:09 by qduperon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

/*
**  Checking if the string is well formated
*/

int			ft_str_is_label(char *str, t_mem *mem)
{
	unsigned long n;

	n = 0;
	if ((ft_strlen(str) > 2 && str[ft_strlen(str) - 1] == ':')
		|| (ft_strlen(str) > 3 && str[ft_strlen(str) - 2] == ':'
			&& str[ft_strlen(str) - 1] == '\n'))
	{
		while (str && str[n] != '\0' && n < ft_strlen(str) - 2)
		{
			if (ft_strchr(LABEL_CHARS, str[n]) == NULL)
				ft_exit("Wrong character in label", -1, mem);
			n++;
		}
		return (1);
	}
	return (0);
}

/*
**  Check in our list of existing labels, if the one we found
**  in the line after an instruction exists in this list
*/

static int	ft_error_label(char *word, t_mem *mem)
{
	ft_putstr(word);
	ft_exit("\nError : bad label", -1, mem);
	return (0);
}

int			ft_label_exist(char *word, t_mem *mem, int where)
{
	int n;
	int ret;

	n = 0;
	if ((word[0] != '%' || word[1] != ':') && (word[0] != ':'))
		ft_error_label(word, mem);
	ret = 0;
	if (word[ft_strlen(word) - 1] == '\n')
		word[ft_strlen(word) - 1] = '\0';
	while (n < mem->n_label)
	{
		(mem->labels[n][ft_strlen(mem->labels[n]) - 1] == ':') ?
			mem->labels[n][ft_strlen(mem->labels[n]) - 1] = '\0' : 0;
		if (ft_strcmp(mem->labels[n], &word[2]) == 0
			|| ft_strcmp(mem->labels[n], &word[1]) == 0)
		{
			ret = mem->i_label[n] - where;
			return (ret);
		}
		n++;
	}
	ft_exit("Label does not exist", -1, mem);
	return (-1);
}

/*
**    filling the memory with the good value
*/

void		fill_label_in_mem(t_mem *mem)
{
	int		n;
	int		ins;
	char	*tmp;

	n = 0;
	while (mem->used_label && mem->used_label[n])
	{
		ins = ft_label_exist(mem->used_label[n], mem, mem->where_used_label[n])
			+ mem->to_add[n];
		tmp = mem->tmp + mem->where_write_label[n];
		if (mem->size_used_label[n] == DIR_SIZE)
			*(int *)(tmp) = reverse_endian_int(ins);
		else
			*(short *)(tmp) = reverse_endian_short((short)ins);
		n++;
	}
}

/*
**  Add a label to our list of existing labels
*/

void		ft_add_label(t_mem *mem, char *str)
{
	int		n;
	char	**tmp;

	n = 0;
	if (!(tmp = (char **)malloc(sizeof(char *) * (mem->n_label + 2))))
		ft_exit("bad malloc ft_add_label", -1, mem);
	while (n < mem->n_label)
	{
		if (!(tmp[n] = ft_strdup(mem->labels[n])))
			ft_exit("Malloc error ft_add_label strdup", -1, mem);
		free(mem->labels[n]);
		n++;
	}
	free(mem->labels);
	if (!(tmp[n] = ft_strdup(str)))
		ft_exit("Error ft_stdrup in ft_add_label", -1, mem);
	tmp[n][ft_strlen(tmp[n]) - 1] = '\0';
	tmp[n + 1] = NULL;
	mem->labels = tmp;
	mem->n_label++;
}
