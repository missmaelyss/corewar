/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 13:48:06 by marnaud           #+#    #+#             */
/*   Updated: 2017/01/24 14:24:49 by marnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_fd	*gnl_new_fd(int fd)
{
	t_fd	*lst;

	lst = (t_fd *)malloc(sizeof(t_fd) * 1);
	(*lst).old = NULL;
	(*lst).fd = fd;
	(*lst).next = NULL;
	(*lst).previous = NULL;
	return (lst);
}

void	fonction_1(char **line, t_fd *lst, const char *s, int i)
{
	size_t	n;
	char	*tmp;
	char	*tmp2;

	n = 0;
	while (s[n] != '\n' && s[n] != '\0')
		n++;
	if (i == 1)
	{
		tmp2 = ft_strsub(s, 0, n);
		tmp = ft_strjoin(lst->old, tmp2);
		free(tmp2);
	}
	else
		tmp = ft_strsub(s, 0, n);
	*line = ft_strdup(tmp);
	free(tmp);
	tmp = ft_strdup(&(s[n + 1]));
	ft_strdel(&(lst->old));
	if (i != 3)
		lst->old = ft_strdup(tmp);
	free(tmp);
}

void	save_join(t_fd *lst, char *buffer)
{
	char	*tmp;

	tmp = ft_strjoin(lst->old, buffer);
	ft_strdel(&(lst->old));
	lst->old = ft_strdup(tmp);
	free(tmp);
}

int		condition(t_fd *lst, int fd, char **line)
{
	char	buffer[BUFF_SIZE + 1];
	int		n;

	n = read(fd, buffer, BUFF_SIZE);
	if (n > 0)
	{
		buffer[n] = '\0';
		if (ft_strchr((const char *)buffer, '\n'))
			fonction_1(line, lst, buffer, 1);
		else
		{
			save_join(lst, buffer);
			get_next_line(fd, line);
		}
	}
	else if (n == 0)
	{
		if (lst->old != NULL && ft_strcmp(lst->old, ""))
			fonction_1(line, lst, lst->old, 3);
		else
			return (0);
	}
	else
		return (-1);
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	static t_fd	*lst = NULL;

	if (fd < 0 || line == NULL)
		return (-1);
	if (lst == NULL)
		lst = gnl_new_fd(fd);
	else
	{
		while (lst->previous != NULL)
			lst = lst->previous;
		while ((*lst).fd != fd && (*lst).next)
			lst = lst->next;
		if ((*lst).fd != fd)
		{
			(*lst).next = gnl_new_fd(fd);
			(*lst).next->previous = lst;
			lst = (*lst).next;
		}
	}
	if (lst->old != NULL && ft_strchr((const char *)lst->old, '\n'))
	{
		fonction_1(line, lst, lst->old, 2);
		return (1);
	}
	return (condition(lst, fd, line));
}
