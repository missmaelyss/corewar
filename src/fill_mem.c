/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 21:15:28 by marnaud           #+#    #+#             */
/*   Updated: 2019/01/15 21:34:38 by marnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/op.h"

static void			direct_char(t_mem *mem, char *word, int i)
{
	int size;
	int ins;

	size = (g_op_tab[i - 1].direct_size == 1) ? IND_SIZE : DIR_SIZE;
	if (!(mem->tmp = (char *)realloc(mem->tmp, mem->i + size)))
		ft_exit("Error : bad malloc", -1, mem);
	mem->tmp[mem->i] = 0;
	if (ft_str_is_digit(&word[1]))
		ins = ft_atoi(&word[1]);
	else
	{
		if (word[ft_strlen(word) - 1] == '\n')
			word[ft_strlen(word) - 1] = '\0';
		ft_stock_label(word, mem, size, 0);
		ins = 0;
	}
	if (size == DIR_SIZE)
		*(int *)(mem->tmp + mem->i) = reverse_endian_int(ins);
	else
		*(short *)(mem->tmp + mem->i) = reverse_endian_short((short)ins);
	(mem->i) += size;
}

static void			register_char(t_mem *mem, char *word, int i, int n)
{
	int size;

	if ((g_op_tab[i - 1].possible_param[n - 1] & T_REG) != T_REG)
		ft_exit("Error : Not a register", -1, mem);
	size = 1;
	if (!(mem->tmp = (char *)realloc(mem->tmp, mem->i + size)))
		ft_exit("Error : bad malloc", -1, mem);
	mem->tmp[mem->i] = ft_atoi(&word[1]);
	(mem->i) += size;
}

static void			other_choice(t_mem *mem, char *word, int i, int n)
{
	int size;
	int ins;

	if ((g_op_tab[i - 1].possible_param[n - 1] & T_IND) != T_IND)
		ft_exit("Error : Bad possible_param", -1, mem);
	size = IND_SIZE;
	if (word[0] == ':')
	{
		if (word[ft_strlen(word) - 1] == '\n')
			word[ft_strlen(word) - 1] = '\0';
		if (ft_strchr(word, '+') != NULL || ft_strchr(word, '-') != NULL)
			ft_exit("Error : +/-", -1, mem);
		else
			ft_stock_label(word, mem, size, 0);
		ins = 0;
	}
	if (!(mem->tmp = (char *)realloc(mem->tmp, mem->i + size)))
		ft_exit("Error : bad malloc", -1, mem);
	*(short *)(mem->tmp + mem->i) =
	reverse_endian_short((short)ft_atoi(&word[0]));
	(mem->i) += size;
}

int					ft_fill_mem(int n, int i, char *word, t_mem *mem)
{
	if (word[0] == DIRECT_CHAR)
	{
		if ((g_op_tab[i - 1].possible_param[n - 1] & T_DIR) != T_DIR)
			ft_exit("Error : Bad possible_param : |%s|\n", -1, mem);
		direct_char(mem, word, i);
		return (DIR_CODE);
	}
	else if (word[0] == REGISTER_CHAR)
	{
		register_char(mem, word, i, n);
		return (REG_CODE);
	}
	else
	{
		other_choice(mem, word, i, n);
		return (IND_CODE);
	}
}
