/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 16:25:09 by marnaud           #+#    #+#             */
/*   Updated: 2018/09/26 17:21:35 by marnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "op.h"

char    *create_line(char *old_line, char new_char)
{
    int     len;
    char    *new_line;
    int     i;
    
    len = 0;
    while (old_line && old_line[len] != 0)
    {
        len++;
    }
    new_line = (char *)malloc((len + 2) * sizeof(char));
    i = 0;
    while (i < len + 2)
    {
        if (i < len)
            new_line[i] = old_line[i];
        else if (i < len + 1)
            new_line[i] = new_char;
        else
            new_line[i] = '\0';
        i++;
    }
    if (len > 0)
        free(old_line);
    return (new_line);
}

int    gnl(int ac, char **av)
{
    int     fd;
    char    c;
    char    *line;
    
	if (ac == 2)
    {
        fd = open(av[1], O_RDONLY);
        if (fd == -1)
            return (-1);
        line = NULL;
        while (read(fd,&c,1) != 0)
        {
            line = create_line(line, c);
            if (c == '\n')
            {
                printf("%s", line);
                free(line);
                line = NULL;
            }
        }
        close(fd);
    }
    return (0);
}

int main (int ac, char **av)
{
    header_t    header;
    gnl(ac, av);
    
    return (0);
}
