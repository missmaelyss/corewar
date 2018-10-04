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

#include "corewar.h"

int 	str_len(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char    *str_addend_char(char **old_line, char new_char)
{
    int     len;
    char    *new_line;
    int     i;
    
    len = 0;
    while (*old_line && (*old_line)[len] != 0)
    {
        len++;
    }
    new_line = (char *)malloc((len + 2) * sizeof(char));
    i = 0;
    while (i < len + 2)
    {
        if (i < len)
            new_line[i] = (*old_line)[i];
        else if (i < len + 1)
            new_line[i] = new_char;
        else
            new_line[i] = '\0';
        i++;
    }
    if (len > 0)
        free(*old_line);
    *old_line = new_line;
    return (new_line);
}

int		str_in_str(char *str, char *line)
{
	int i;
	int n;

	i = 0;
	n = 0;
	while (line[i])
	{
		while (line[i + n] == str[n])
			n++;
		if (str[n] == '\0' && n > 0)
			return (i + n);
		else
			n = 0;
		i++;
	}
	return 0;
}

char	*str_suppr_comment(char **line)
{
	char *new;
	int i;

	i = 0;
	while ((*line)[i] && (*line)[i] != '#')
		i++;
	new = (char *)malloc((i + 1) * sizeof(char));
	i = 0;
	while ((*line)[i] && (*line)[i] != '#')
	{
		new[i] = (*line)[i];
		i++;
	}
	if ((*line)[i] != '\0')
	{
		new[i] = '\n';
		i++;
	}
	new[i] = '\0';
	free(*line);
	*line = new;
	return (new);
}

int 	nb_arround_spaces(char *line)
{
	int i;
	int n;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	n = 0;
	while (line[str_len(line) - n] == ' ' || line[str_len(line) - n] == '\0' || line[str_len(line) - n] == '\n')
	{
		if (line[str_len(line) - n] == ' ')
			i++;
		n++;
	}
	return (i);
}

char	*str_suppr_arround_spaces(char **line)
{
	char *new;
	int i;
	int n;

	new = (char *)malloc((str_len(*line) + 1 - nb_arround_spaces(*line)) * sizeof(char));
	i = 0;
	n = 0;
	while ((*line)[i] && (*line)[i] == ' ')
		i++;
	while ((*line)[i + n] && n < str_len(*line) + 1 - nb_arround_spaces(*line))
	{
		new[n] = (*line)[i + n];
		n++;
	}
	new[n] = '\0';
	free(*line);
	*line = new;
	return (new);
}

char	*str_take_content(char **str, t_env *env)
{
	char *new;
	int i;

	i = 0;
	if ((*str)[0] != '\"')
		return (NULL);
	else
	{
		env->quote_open = 1;
		new = (char *)malloc((str_len(*str)) * sizeof(char));
		while ((*str)[i + 1] && i < str_len(*str))
		{
			if ((*str)[i + 1] == '\"')
				env->quote_open = 0;
			if (env->quote_open == 1)
				new[i] = (*str)[i + 1];
			else if ((*str)[i + 1] != '\n' && (*str)[i + 1] != '\0' && (*str)[i + 1] != '\"')
			{
				free(new);
				new = NULL;
			}
			i++;
		}
		if (new != NULL)
			new[i] = '\0';
		return (new);
	}

}

char 	*str_cpy(char *str)
{
	char 	*new;
	int 	i;

	i = 0;
	new = (char *)malloc((str_len(str) + 1) * sizeof(char));
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

void	read_line(char *line, t_env *env)
{
	char *str;

	if (env->name == 0 || env->comment == 0)
	{
		if (str_in_str(NAME_CMD_STRING, line) == str_len(NAME_CMD_STRING) && env->name == 0)
		{
			str = str_cpy(&line[str_in_str(NAME_CMD_STRING, line)]);
			str_suppr_arround_spaces(&str);
			printf("%s|\n", str);
			printf("Found '.name' : %s|\n", str_take_content(&str, env));
		}
		else if (str_in_str(COMMENT_CMD_STRING, line) == str_len(COMMENT_CMD_STRING) && env->comment == 0)
			printf("Found '.comment'\n");
		else
			printf("Error\n");
	}
}

int    gnl(int ac, char **av, t_env *env)
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
            str_addend_char(&line, c);
            if (c == '\n')
            {
            	str_suppr_comment(&line);
            	str_suppr_arround_spaces(&line);
             	read_line(line, env);
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
    t_env		env;
    env.name = 0;
    env.comment = 0;
    env.quote_open = 0;
    env.header.magic = COREWAR_EXEC_MAGIC;

    //printf("START :\nmagic_env : %d\nprog_name_env : %s\nprog_size_env : %d\ncomment_env : %s\n", env.header.magic, env.header.prog_name, env.header.prog_size, env.header.comment);
    gnl(ac, av, &env);
    //printf("END :\nmagic_env : %d\nprog_name_env : %s\nprog_size_env : %d\ncomment_env : %s\n", env.header.magic, env.header.prog_name, env.header.prog_size, env.header.comment);
    
    return (0);
}