/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaud <marnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 16:32:26 by marnaud           #+#    #+#             */
/*   Updated: 2019/01/22 13:26:55 by qduperon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

void	ft_freetab(char **tab)
{
	int	i;

	i = 0;
	if (tab == NULL)
		return ;
	while (tab[i] != NULL)
	{
		ft_strdel(&tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
}

void	ft_exit(char *exit_msg, int status, t_mem *mem)
{
	if (mem->file != NULL)
		free(mem->file);
	ft_freetab(mem->data);
	if (mem->tmp != NULL)
		free(mem->tmp);
	ft_freetab(mem->labels);
	if (mem->i_label != NULL)
		free(mem->i_label);
	if (mem->where_used_label != NULL)
		free(mem->where_used_label);
	if (mem->where_write_label != NULL)
		free(mem->where_write_label);
	ft_freetab(mem->used_label);
	if (mem->to_add != NULL)
		free(mem->size_used_label);
	if (mem->file != NULL)
		free(mem->to_add);
	if (exit_msg != NULL)
	{
		ft_putendl(exit_msg);
		exit(status);
	}
}
