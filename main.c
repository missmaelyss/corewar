#include "libft/libft.h"
#include "op.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>

int create_new_cor(char const *av)
{
  char *name_cor;
  int fd_cor;

  if (ft_strlen(av) < 3 || (av[ft_strlen(av) - 2] != '.' &&
  av[ft_strlen(av) - 1] != 's'))
    return(0);
  name_cor = (char *)malloc((ft_strlen(av) + 3) * sizeof(char));
  ft_strcpy(name_cor, av);
  name_cor[ft_strlen(av) - 1] = 'c';
  name_cor[ft_strlen(av)] = 'o';
  name_cor[ft_strlen(av) + 1] = 'r';
  name_cor[ft_strlen(av) + 2] = '\0';
  fd_cor = open(name_cor, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
  return (fd_cor);
}

int	ft_strchrword(char *str, char *word)
{
	int words;
	char *ptr;
	int n;

	words = 0;
	n = 0;
	if ((ptr = ft_strstr(str, word)) != NULL)
	{
		while (&str[n] != ptr && str[n])
		{
            if (str[n] != ' ' && str[n] != '\t' && &str[n] != ptr && str[n])
            {
                words++;
                while (str[n] != ' ' && str[n] != '\t' && &str[n] != ptr && str[n])
                    n++;
            }
            else
                n++;
		}
        words++;
	}
	return (words);
}

int fill_mem(t_mem *mem, char const *av)
{
  int fd_r;
  char buffer[1000];
  char *tmp;

  mem->file = NULL;
  fd_r = open(av, O_RDONLY);
  while (read(fd_r, buffer, 1000))
  {
    tmp = ft_strjoin(mem->file, buffer);
    free(mem->file);
    mem->file = tmp;
    ft_bzero(buffer, 1000);
  }
  mem->data = ft_strsplit(mem->file, '\n');
  return (fd_r);
}

int fill_header_name(t_mem *mem, int n)
{
  char  *start;
  char  *tmp;
  int   i;

  i = 1;
  start = ft_strdup(ft_strchr(mem->data[n], '"'));
  while (start[i] != '"' && i - 1 < PROG_NAME_LENGTH + 1)
  {
    mem->header.prog_name[i - 1] = start[i];
    if (start[i + 1] == 0)
    {
      n++;
      tmp = ft_strjoin(start,"\n");
      free(start);
      start = ft_strjoin(tmp, mem->data[n]);
      free(tmp);
    }
    i++;
  }
  free(start);
  return (1);
}

int fill_header_comment(t_mem *mem, int n)
{
  char  *start;
  char  *tmp;
  int   i;

  i = 1;
  start = ft_strdup(ft_strchr(mem->data[n], '"'));
  while (start[i] != '"' && i - 1 < COMMENT_LENGTH + 1 && start[i] != 0)
  {
    mem->header.comment[i - 1] = start[i];
    if (start[i + 1] == 0)
    {
      n++;
      tmp = ft_strjoin(start,"\n");
      free(start);
      start = ft_strjoin(tmp, mem->data[n]);
      free(tmp);
    }
    i++;
  }
  free(start);
  return (1);
}

int ft_del_char_ptr(char **tmp)
{
  int i;

  i = 0;
  while (tmp[i] != NULL)
  {
    free(tmp[i]);
    i++;
  }
  free(tmp);
  return (1);
}

int ft_str_in_op_tab(char *str)
{
  int n;
  int i;

  n = 0;
  i = 0;
  while (str[i] == '\t')
    i++;
  while (op_tab[n].name != NULL)
  {
    if (ft_strcmp(op_tab[n].name, &str[i]) == 0)
    {
      return (n + 1);
    }
    n++;
  }
  return (0);
}

int main(int ac, char const *av[])
{
  t_mem mem;
  char  **tmp;
  int   n = 0;
  int   i;

  if (ac > 1)
  {
    fill_mem(&mem, av[1]);
    while (mem.data[n] != NULL)
    {
      tmp = ft_strsplit(mem.data[n], ' ');
      if (ft_strcmp(".comment", tmp[0]) == 0)
      {
        fill_header_comment(&mem, n);
        //printf("%s\n", mem.header.comment);
      }
      if (ft_strcmp(".name", tmp[0]) == 0)
      {
        fill_header_name(&mem, n);
        //printf("%s\n", mem.header.prog_name);
      }
      if ((i = ft_str_in_op_tab(tmp[0])) != 0)
      {
        printf("On a trouve l'instruction : %s (%d), en tant que 1er mot dans la ligne: %s\n", op_tab[i - 1].name, i, mem.data[n]);
      }
      ft_del_char_ptr(tmp);
      n++;
    }
  }
	return 0;
}
