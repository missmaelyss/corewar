#include "libft/libft.h"
#include "op.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>

/*
**  create_new_cor(char const *av)
**  is a fonction for creating a new file.cor
**  we need to check the errors
*/

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

/*
**  ft_strchrword(char *str, char *word)
**  return the number of time there is the word in the string
*/

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

/*
**  int fill_mem(t_mem *mem, char const *av)
**  fill the string we will put on the final file
**  this sting is stored in t_mem mem.tmp;
**  the index of the pointer of this string is t_mem mem.i;
*/

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
  mem->i = 0;
  return (fd_r);
}

/*
**  int fill_header_name(t_mem *mem, int n)
**  fill the name in the header (header.name)
**  the header is in t_mem mem.header
*/

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

/*
**  int fill_header_comment(t_mem *mem, int n)
**  fill the comment in the header (header.comment)
**  the header is in t_mem mem.header
*/

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

/*
**  ft_del_char_ptr(char **tmp)
**  to del a pointer of strings and the strings inside
*/

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

/*
**  We are looking if the string contains one of the instruction
**  in op_tab (op.c)
*/

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

/*
**  ft_mem_instr(int i, char *word, t_mem *mem)
**  store in t_mem mem.tmp the opcode of the instruction
**  i is the index of the instruction in op_tab
*/

int ft_mem_instr(int i, char *word, t_mem *mem)
{
  int   size;
  int   n;

  if (ft_strcmp(op_tab[i - 1].name, word) == 0)
  {
    size = 1;
    if (!(mem->tmp = (char *)realloc(mem->tmp, mem->i + size)))
      return (0);
    n = 0;
    mem->tmp[mem->i + n] = op_tab[i - 1].opcode;
    (mem->i) += size;
  }
  else
  {

  }
  return (1);
}

/*
**  void ft_clear_word(char **word)
**  clear a word of '\t' and ','
*/

void ft_clear_word(char **word)
{
  int n;

  n = 0;
  while ((*word)[n] != '\0')
  {
    if ((*word)[n] == '\t' || (*word)[n] == ',')
    {
      while ((*word)[n] != '\0')
      {
        (*word)[n] = (*word)[n + 1];
        n++;
      }
      n = -1;
    }
    n++;
  }
}

/*
**  int   ft_instruction(int i, char **word_in_line, t_mem *mem)
**  for now, this function is a way to cross a string word by words
**  checking if the nb of argument after the instruction is the same as
**  in op_tab
*/

int   ft_instruction(int i, char **word_in_line, t_mem *mem)
{
  int n;

  n = 0;
  while (word_in_line[n] != NULL)
  {
    if (ft_strrchr(word_in_line[n], '#') != NULL)
      word_in_line[n + 1] = NULL;
    ft_clear_word(&(word_in_line[n]));
    ft_mem_instr(i, word_in_line[n], mem);
    n++;
  }
  if (op_tab[i - 1].param_nb - (n - 1) != 0)
  {
    printf("Mauvais nombre d'argument dans l'instruction\n");
    return (0);
  }
  return (1);
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
        ft_instruction(i, tmp, &mem);
        //printf("On a trouve l'instruction : %s (%d), en tant que 1er mot dans la ligne: %s\n", op_tab[i - 1].name, i, mem.data[n]);
      }
      ft_del_char_ptr(tmp);
      n++;
    }

    printf("%s\n", mem.tmp);
  }
	return 0;
}
