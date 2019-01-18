/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 16:37:56 by marnaud           #+#    #+#             */
/*   Updated: 2019/01/15 16:40:16 by marnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/op.h"

/*
**  ft_mem_instr(int i, char *word, t_mem *mem)
**  store in t_mem mem.tmp the opcode of the instruction
**  i is the index of the instruction in g_op_tab
*/

int			ft_mem_instr(int n, int i, char *word, t_mem *mem)
{
	int				size;

	if (ft_strcmp(g_op_tab[i - 1].name, word) == 0)
	{
		mem->where = mem->i + 1;
		size = 1 + g_op_tab[i - 1].encoding_byte;
		if (!(mem->tmp = (char *)realloc(mem->tmp, mem->i + size)))
			return (0);
		mem->tmp[mem->i] = g_op_tab[i - 1].opcode;
		if (g_op_tab[i - 1].encoding_byte)
		{
			mem->enc_b_i = mem->i;
			mem->tmp[mem->i + 1] = 0;
		}
		else
			mem->enc_b_i = -1;
		(mem->i) += size;
		return (0);
	}
	else
		return (ft_fill_mem(n, i, word, mem));
}

static void	del_end_of_str(int u, char **word_in_line)
{
	while (word_in_line[u])
	{
		free(word_in_line[u]);
		word_in_line[u] = NULL;
		u++;
	}
}

static	int	ft_while_instruction(int i, char **word_in_line, t_mem *mem, int *n)
{
	unsigned char	enc_b;
	char			*tmp;
	int				tmp2;

	enc_b = 0;
	while (word_in_line[*n] != NULL)
	{
		tmp = ft_strrchr(word_in_line[*n], COMMENT_CHAR);
		if (tmp != NULL)
		{
			tmp[0] = '\0';
			del_end_of_str(*n + 1, word_in_line);
		}
		if (word_in_line[*n][0] == '\0' || word_in_line[*n][0] == '\n')
		{
			del_end_of_str(*n, word_in_line);
			break ;
		}
		if ((tmp2 = ft_mem_instr(*n, i, word_in_line[*n], mem)) == -1)
			return (-1);
		enc_b += tmp2;
		enc_b = enc_b << 2;
		(*n)++;
	}
	return (enc_b);
}

/*
**  int   ft_instruction(int i, char **word_in_line, t_mem *mem)
**  for now, this function is a way to cross a string word by words
**  checking if the nb of argument after the instruction is the same as
**  in g_op_tab
*/

int			ft_instruction(int i, char **word_in_line, t_mem *mem)
{
	int				n;
	unsigned char	enc_b;

	n = 0;
	enc_b = ft_while_instruction(i, word_in_line, mem, &n);
	enc_b = enc_b << (6 - ((n - 1) * 2));
	if (mem->enc_b_i > -1)
		mem->tmp[mem->enc_b_i + 1] = enc_b;
	if (g_op_tab[i - 1].param_nb - (n - 1) != 0)
		ft_exit("Mauvais nombre d'argument dans l'instruction\n", -1, mem);
	return (1);
}

/*
**  We are looking if the string contains one of the instruction
**  in g_op_tab (op.c)
*/

int			ft_str_in_op_tab(char *str)
{
	int n;
	int i;

	n = 0;
	i = 0;
	while (str[i] == '\t' || str[i] == ' ')
		i++;
	while (g_op_tab[n].name != NULL)
	{
		if (ft_strcmp(g_op_tab[n].name, &str[i]) == 0)
		{
			return (n + 1);
		}
		n++;
	}
	return (0);
}
