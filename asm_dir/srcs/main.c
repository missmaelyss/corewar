/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaud <marnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 16:32:26 by marnaud           #+#    #+#             */
/*   Updated: 2019/01/22 13:58:40 by qduperon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

/*
**  unsigned int		magic;
**  char				prog_name[PROG_NAME_LENGTH + 1];
**  unsigned int		prog_size;
**  char				comment[COMMENT_LENGTH + 1];
*/

static void		handle_line(int *n, char **tmp, t_mem *mem)
{
	if (tmp[0] && ft_strcmp(".comment", tmp[0]) == 0)
	{
		*n = fill_header_comment(mem, *n);
		(mem->good)++;
	}
	else if (tmp[0] && ft_strcmp(".name", tmp[0]) == 0)
	{
		(mem->good)++;
		*n = fill_header_name(mem, *n);
	}
	else if (tmp[0] && ft_str_is_label(tmp[0], mem))
	{
		if (tmp[1] && tmp[1][0] != COMMENT_CHAR && ft_str_in_op_tab(tmp[1]) == 0
			&& tmp[1][0] != '\0' && tmp[1][0] != ' ' && tmp[1][0] != '\n'
				&& tmp[1][0] != '\t' && ft_strlen(tmp[1]) > 1)
			ft_exit("Error: Bad character after label", -1, mem);
		ft_add_label(mem, tmp[0]);
		ft_label_place(mem);
	}
	else if (tmp[0] && tmp[0][0] != COMMENT_CHAR && ft_str_in_op_tab(tmp[0])
		== 0 && tmp[0][0] != '\0' && tmp[0][0] != ' ' && tmp[0][0] != '\n'
			&& tmp[0][0] != '\t' && ft_strlen(tmp[0]) > 1)
		ft_exit("Error: Not accepted word", -1, mem);
}

static void		instruction_in_line(int n, char **tmp, t_mem *mem)
{
	if (mem->good < 2)
		ft_exit("Missing comment or name", -1, mem);
	if (ft_str_in_op_tab(tmp[0]) != 0)
	{
		if (ft_instruction(ft_str_in_op_tab(tmp[0]), tmp, mem) == -1)
		{
			ft_putstr("Lexical error at [");
			ft_putnbr(n + 1);
			ft_putstr(":1");
			ft_exit("]", -1, mem);
		}
		(mem->good)++;
	}
	else
	{
		if (ft_instruction(ft_str_in_op_tab(tmp[1]), &tmp[1], mem) == -1)
		{
			ft_putstr("Lexical error at [");
			ft_putnbr(n + 1);
			ft_putstr(":2");
			ft_exit("]", -1, mem);
		}
		(mem->good)++;
	}
}

static void		file_end(t_mem *mem, char const *av[])
{
	int fd;

	if (mem->good < 3)
		ft_exit("Syntax error no instruction", -1, mem);
	fill_label_in_mem(mem);
	fd = create_new_cor(av[1]);
	if (fd == -1)
		ft_exit("Impossible to create .cor", -1, mem);
	mem->header.magic = reverse_endian_int(COREWAR_EXEC_MAGIC);
	mem->header.prog_size = reverse_endian_int(mem->i);
	write(fd, &(mem->header), sizeof(mem->header));
	write(fd, mem->tmp, mem->i);
	ft_exit("New .cor created", 1, mem);
}

static void		init_mem_data(int n, t_mem *mem)
{
	mem->data[n] = ft_strrpl(mem->data[n], mem->data[n], ';', COMMENT_CHAR);
	mem->data[n] = add_space_direct_char(mem->data[n]);
	mem->data[n] = remove_space_add_char(mem->data[n]);
}

int				main(int ac, char const *av[])
{
	t_mem	mem;
	char	**tmp;
	int		n;

	n = 0;
	ft_bzero(&mem, sizeof(mem));
	if (ac > 1)
	{
		fill_mem(&mem, av[1]);
		while (mem.data && mem.data[n] != NULL)
		{
			init_mem_data(n, &mem);
			tmp = ft_strsplit_2(mem.data[n], " \t,", &mem);
			handle_line(&n, tmp, &mem);
			if (tmp[0] && ((tmp[1] && ft_str_in_op_tab(tmp[1]) != 0
				&& ft_str_is_label(tmp[0], &mem))
					|| ft_str_in_op_tab(tmp[0]) != 0))
				instruction_in_line(n, tmp, &mem);
			ft_freetab(tmp);
			n++;
		}
		file_end(&mem, av);
	}
	return (0);
}
