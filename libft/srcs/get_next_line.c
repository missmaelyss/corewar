/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbrucker <nbrucker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 19:33:49 by nbrucker          #+#    #+#             */
/*   Updated: 2017/12/02 19:33:49 by nbrucker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_index(char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

static int	ft_cut(t_gnl **current, char **line)
{
	char	*tmp;

	if (ft_index((*current)->str, '\n') == -1)
	{
		if ((*line = ft_strdup((*current)->str)) == NULL)
			return (-1);
		ft_strdel(&(*current)->str);
		return (1);
	}
	*line = ft_strsub((*current)->str, 0, ft_index((*current)->str, '\n'));
	if (*line == NULL)
		return (-1);
	if ((tmp = ft_strdup((*current)->str)) == NULL)
		return (-1);
	ft_strdel(&(*current)->str);
	(*current)->str = ft_strsub(tmp, ft_strlen(*line) + 1,
		ft_strlen(tmp) - ft_strlen(*line) - 1);
	if ((*current)->str == NULL)
		return (-1);
	ft_strdel(&tmp);
	return (1);
}

static int	ft_read(t_gnl **current, int fd, char **line)
{
	char	buf[BUFF_SIZE + 1];
	char	*tmp;

	if ((*current)->str == NULL)
		if (((*current)->str = ft_strnew(1)) == NULL)
			return (-1);
	while (ft_index((*current)->str, '\n') == -1 &&
		((*current)->ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		if ((tmp = ft_strdup((*current)->str)) == NULL)
			return (-1);
		ft_strdel(&(*current)->str);
		buf[(*current)->ret] = 0;
		if (((*current)->str = ft_strjoin(tmp, buf)) == NULL)
			return (-1);
		ft_strdel(&tmp);
	}
	if ((*current)->ret == -1)
		return (-1);
	if (ft_cut(current, line) == -1)
		return (-1);
	return (1);
}

static int	ft_make_lst(t_gnl **current, t_gnl **lst, int fd)
{
	t_gnl	*new;

	if ((new = (t_gnl*)malloc(sizeof(t_gnl))) == NULL)
		return (-1);
	new->fd = fd;
	new->ret = 1;
	new->next = NULL;
	new->str = NULL;
	if (*current != NULL)
		(*current)->next = new;
	*current = new;
	if (*lst == NULL)
		*lst = *current;
	return (1);
}

int			get_next_line(const int fd, char **line)
{
	static t_gnl	*lst;
	t_gnl			*current;
	int				i;

	if (fd < 0 || BUFF_SIZE < 1 || line == NULL)
		return (-1);
	current = lst;
	i = -1;
	while (current && current->next)
	{
		if (current->fd == fd)
		{
			i = 1;
			break ;
		}
		current = current->next;
	}
	if (i == -1 && (!current || current->fd != fd))
		if (ft_make_lst(&current, &lst, fd) == -1)
			return (-1);
	if (ft_read(&current, fd, line) == -1)
		return (-1);
	if (ft_strcmp(*line, "") == 0 && current->ret == 0)
		return (0);
	return (1);
}
