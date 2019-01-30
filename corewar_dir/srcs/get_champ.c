/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_champ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <nbrucker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 19:12:18 by nbrucker          #+#    #+#             */
/*   Updated: 2018/03/06 15:42:10 by nbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "op.h"
#include "../../libft/includes/libft.h"

void	ft_get_champ_magic(t_champ *champ)
{
	if (champ->len < 4)
	{
		ft_putstr(champ->file);
		ft_error(" : too small");
	}
	champ->magic = (champ->content[0] << 24) + (champ->content[1]
	<< 16) + (champ->content[2] << 8) + champ->content[3];
	if (champ->magic != COREWAR_EXEC_MAGIC)
	{
		ft_putstr(champ->file);
		ft_error(" : wrong magic code !");
	}
	ft_get_champ_name(champ);
	ft_get_champ_size(champ);
	ft_get_champ_comment(champ);
	ft_get_champ_code(champ);
}

void	ft_get_champ_name(t_champ *champ)
{
	int	i;

	if (champ->len < 4 + PROG_NAME_LENGTH)
	{
		ft_putstr(champ->file);
		ft_error(" : too small");
	}
	if ((champ->name = ft_strnew(PROG_NAME_LENGTH + 1)) == NULL)
		ft_error("Malloc error");
	i = 0;
	while (i < PROG_NAME_LENGTH)
	{
		champ->name[i] = champ->content[i + 4];
		i++;
	}
}

void	ft_get_champ_size(t_champ *champ)
{
	if (champ->len < 12 + PROG_NAME_LENGTH)
	{
		ft_putstr(champ->file);
		ft_error(" : too small");
	}
	champ->size = (champ->content[8 + PROG_NAME_LENGTH] << 24)
	+ (champ->content[9 + PROG_NAME_LENGTH] << 16) + (champ->content[10
	+ PROG_NAME_LENGTH] << 8) + champ->content[11 + PROG_NAME_LENGTH];
	if (champ->size > CHAMP_MAX_SIZE)
	{
		ft_putstr(champ->file);
		ft_error(" : too big");
	}
}

void	ft_get_champ_comment(t_champ *champ)
{
	int	i;

	if (champ->len < 12 + PROG_NAME_LENGTH + COMMENT_LENGTH)
	{
		ft_putstr(champ->file);
		ft_error(" : too small");
	}
	if ((champ->comment = ft_strnew(COMMENT_LENGTH + 1)) == NULL)
		ft_error("Malloc error");
	i = 0;
	while (i < COMMENT_LENGTH)
	{
		champ->comment[i] = champ->content[i + 12 + PROG_NAME_LENGTH];
		i++;
	}
}

void	ft_get_champ_code(t_champ *champ)
{
	unsigned int	i;

	if ((unsigned int)champ->len < 16 + PROG_NAME_LENGTH
	+ COMMENT_LENGTH + champ->size)
	{
		ft_putstr(champ->file);
		ft_error(" : too small");
	}
	else if ((unsigned int)champ->len > 16 + PROG_NAME_LENGTH
	+ COMMENT_LENGTH + champ->size)
	{
		ft_putstr(champ->file);
		ft_error(" : too big");
	}
	if ((champ->code = (unsigned char*)malloc(sizeof(unsigned char)
	* champ->size)) == NULL)
		ft_error("Malloc error");
	i = 0;
	while (i < champ->size)
	{
		champ->code[i] = champ->content[i + 16 + PROG_NAME_LENGTH
		+ COMMENT_LENGTH];
		i++;
	}
}
