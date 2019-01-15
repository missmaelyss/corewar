/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_label.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 16:32:26 by marnaud           #+#    #+#             */
/*   Updated: 2019/01/15 16:35:54 by marnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/op.h"

/*
**  typedef struct        s_tmp_lab
**  {
**    char        **used_label;
**    int         *where_used_label;
**    int         *where_write_label;
**    int         *size_used_label;
**    int         *to_add;
**  }                    t_tmp_lab;
**
**  Stock the label info in memory in order to fill it later
*/

static t_tmp_lab	ft_init_tmp_label(int size_tab, t_mem *mem, int *n)
{
	t_tmp_lab	tmp;

	tmp.used_label = (char **)malloc(sizeof(char *) * (size_tab + 2));
	tmp.where_used_label = (int *)malloc(sizeof(int) * (size_tab + 1));
	tmp.where_write_label = (int *)malloc(sizeof(int) * (size_tab + 1));
	tmp.size_used_label = (int *)malloc(sizeof(int) * (size_tab + 1));
	tmp.to_add = (int *)malloc(sizeof(int) * (size_tab + 1));
	*n = 0;
	while ((*n) < size_tab)
	{
		tmp.used_label[*n] = ft_strdup(mem->used_label[*n]);
		tmp.where_used_label[*n] = mem->where_used_label[*n];
		tmp.where_write_label[*n] = mem->where_write_label[*n];
		tmp.size_used_label[*n] = mem->size_used_label[*n];
		tmp.to_add[*n] = mem->to_add[*n];
		free(mem->used_label[*n]);
		(*n)++;
	}
	free(mem->used_label);
	free(mem->where_used_label);
	free(mem->where_write_label);
	free(mem->size_used_label);
	free(mem->to_add);
	return (tmp);
}

void				ft_stock_label(char *word, t_mem *mem, int size, int add)
{
	t_tmp_lab	tmp;
	int			size_tab;
	int			n;

	size_tab = 0;
	while (mem->used_label && mem->used_label[size_tab] != NULL)
		size_tab++;
	tmp = ft_init_tmp_label(size_tab, mem, &n);
	tmp.used_label[n] = ft_strdup(word);
	tmp.used_label[n + 1] = NULL;
	tmp.where_used_label[n] = mem->where;
	tmp.where_write_label[n] = mem->i;
	tmp.size_used_label[n] = size;
	tmp.to_add[n] = add;
	mem->used_label = tmp.used_label;
	mem->where_used_label = tmp.where_used_label;
	mem->where_write_label = tmp.where_write_label;
	mem->size_used_label = tmp.size_used_label;
	mem->to_add = tmp.to_add;
}

/*
**  Add a new label place
*/

void				ft_label_place(t_mem *mem)
{
	int n;
	int *tmp;

	n = 0;
	tmp = (int *)malloc(sizeof(int) * (mem->n_label));
	while (n < mem->n_label - 1)
	{
		tmp[n] = mem->i_label[n];
		n++;
	}
	free(mem->i_label);
	tmp[n] = mem->i + 1;
	mem->i_label = tmp;
	n = 0;
}
