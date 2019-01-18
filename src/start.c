/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 16:32:26 by marnaud           #+#    #+#             */
/*   Updated: 2019/01/17 20:06:18 by marnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/op.h"

/*
**  int fill_mem(t_mem *mem, char const *av)
**  fill the string we will put on the final file
**  this sting is stored in t_mem mem.tmp;
**  the index of the pointer of this string is t_mem mem.i;
*/

int			fill_mem(t_mem *mem, char const *av)
{
	int		fd_r;
	char	buffer[1000];
	char	*tmp;
	int		cpt;

	mem->file = NULL;
	fd_r = open(av, O_RDONLY | O_NOFOLLOW);
	if (ft_strlen(av) < 3 || (av[ft_strlen(av) - 2] != '.' ||
	av[ft_strlen(av) - 1] != 's') || fd_r == -1)
		ft_exit("Bad file\nusage: ./asm [file].s", -1, mem);
	ft_bzero(buffer, 1000);
	while ((cpt = read(fd_r, buffer, 1000 - 1)) > 0)
	{
		mem->nb_c += cpt;
		tmp = ft_strjoin(mem->file, buffer);
		free(mem->file);
		mem->file = tmp;
		ft_bzero(buffer, 1000);
	}
	if (cpt < 0)
		ft_exit("Bad file\nusage: ./asm [file].s", -1, mem);
	mem->data = ft_strsplit_3(mem->file, "\n");
	mem->i = 0;
	return (fd_r);
}

static char	*new_line(t_mem *mem, int *n, int *u)
{
	(*n)++;
	*u = -1;
	mem->p_c += 1;
	return (mem->data[*n]);
}

/*
**  int fill_header_name(t_mem *mem, int n)
**  fill the name in the header (header.name)
**  the header is in t_mem mem.header
*/

int			fill_header_name(t_mem *mem, int n)
{
	char	*start;
	int		i;
	int		u;

	i = 0;
	u = 1;
	start = ft_strchr(mem->data[n], '"');
	if (!start)
		ft_exit("Error: Bad name", -1, mem);
	mem->p_c += ft_strlen(mem->data[n]) - ft_strlen(start);
	while (i < COMMENT_LENGTH && mem->p_c < mem->nb_c)
	{
		if (start[u] == '"')
			break ;
		mem->header.prog_name[i] = start[u];
		if (start[u + 1] == 0 && i < COMMENT_LENGTH)
			start = new_line(mem, &n, &u);
		mem->p_c += 1;
		i++;
		u++;
		if (mem->p_c >= mem->nb_c)
			ft_exit("Error: Bad name", -1, mem);
	}
	return (n);
}

/*
**  int fill_header_comment(t_mem *mem, int n)
**  fill the comment in the header (header.comment)
**  the header is in t_mem mem.header
*/

int			fill_header_comment(t_mem *mem, int n)
{
	char	*start;
	int		i;
	int		u;

	i = 0;
	u = 1;
	mem->p_c += 1;
	start = ft_strchr(mem->data[n], '"');
	if (!start)
		ft_exit("Error: Bad comment", -1, mem);
	mem->p_c += ft_strlen(mem->data[n]) - ft_strlen(start);
	while (i < COMMENT_LENGTH && mem->p_c < mem->nb_c)
	{
		if (start[u] == '"')
			break ;
		mem->header.comment[i] = start[u];
		if (start[u + 1] == 0 && i < COMMENT_LENGTH)
			start = new_line(mem, &n, &u);
		mem->p_c += 1;
		i++;
		u++;
		if (mem->p_c >= mem->nb_c)
			ft_exit("Error: Bad comment", -1, mem);
	}
	return (n);
}

/*
**  create_new_cor(char const *av)
**  is a fonction for creating a new file.cor
**  we need to check the errors
*/

int			create_new_cor(char const *av)
{
	char	*name_cor;
	int		fd_cor;

	if (ft_strlen(av) < 3 || (av[ft_strlen(av) - 2] != '.' &&
	av[ft_strlen(av) - 1] != 's'))
		return (-1);
	name_cor = (char *)malloc((ft_strlen(av) + 3) * sizeof(char));
	ft_strcpy(name_cor, av);
	name_cor[ft_strlen(av) - 1] = 'c';
	name_cor[ft_strlen(av)] = 'o';
	name_cor[ft_strlen(av) + 1] = 'r';
	name_cor[ft_strlen(av) + 2] = '\0';
	fd_cor = open(name_cor, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
	ft_strdel(&name_cor);
	return (fd_cor);
}
