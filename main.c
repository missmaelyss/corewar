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
  while (read(fd_r, buffer, 1000 - 1))
  {
    tmp = ft_strjoin(mem->file, buffer);
    free(mem->file);
    mem->file = tmp;
    ft_bzero(buffer, 1000);
  }
  mem->data = ft_strsplit_3(mem->file, "\n");
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
  int   i;
  int   u;

  i = 0;
  u = 1;
  start = ft_strchr(mem->data[n], '"');
  while (i < COMMENT_LENGTH && start[u] != 0)
  {
    if (start[u] == '"' && u != 0)
      break;
    mem->header.prog_name[i] = start[u];
    if (start[u + 1] == 0 && i < COMMENT_LENGTH)
    {
      n++;
      u = -1;
      start = mem->data[n];
    }
    i++;
    u++;
  }
  return (n);
}

/*
**  int fill_header_comment(t_mem *mem, int n)
**  fill the comment in the header (header.comment)
**  the header is in t_mem mem.header
*/

int fill_header_comment(t_mem *mem, int n)
{
  char  *start;
  int   i;
  int   u;

  i = 0;
  u = 1;
  start = ft_strchr(mem->data[n], '"');
  while (i < COMMENT_LENGTH && start[u] != 0)
  {
    if (start[u] == '"' && u != 0)
      break;
    mem->header.comment[i] = start[u];
    if (start[u + 1] == 0 && i < COMMENT_LENGTH)
    {
      n++;
      u = -1;
      start = mem->data[n];
    }
    i++;
    u++;
  }
  return (n);
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
  while (str[i] == '\t' || str[i] == ' ')
    i++;
  while (op_tab[n].name != NULL)
  {
    // printf("|%s|\n", &str[i]);
    if (ft_strcmp(op_tab[n].name, &str[i]) == 0)
    {
      return (n + 1);
    }
    n++;
  }
  return (0);
}

int    ft_str_is_digit(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (!(ft_isdigit(str[i])) && str[i] != '\n' && str[i] != '-')
            return (0);
        i++;
    }
    return (1);
}

int reverse_endian_int(int a)
{
  char  ret[4];
  char  tmp;

  *(int *)ret = a;
  tmp = ret[0];
  ret[0] = ret[3];
  ret[3] = tmp;
  tmp = ret[1];
  ret[1] = ret[2];
  ret[2] = tmp;
  return (*(int *)ret);
   // return ((a << 24) & ((a & 0xff00) << 8) & ((a & 0xff0000) >> 8) & (a >> 24));
}

short reverse_endian_short(short a)
{
  char  ret[2];
  char  tmp;

  *(short *)ret = a;
  tmp = ret[0];
  ret[0] = ret[1];
  ret[1] = tmp;
  return (*(short *)ret);
}

int   ft_label_exist(char *word, t_mem *mem, int where)
{
  int n;
  int ret;

  n = 0;
  if ((word[0] != '%' || word[1] != ':') && (word[0] != ':'))
  {
    // printf("%s\n", word);
    ft_putstr(word);
    ft_exit("\nError : label mal ecrit : |%s|\n", -1, mem);
    return (0);
  }
  ret = 0;
  if (word[ft_strlen(word) - 1] == '\n')
    word[ft_strlen(word) - 1] = '\0';
  while (n < mem->n_label)
  {
    (mem->labels[n][ft_strlen(mem->labels[n]) - 1] == ':') ? mem->labels[n][ft_strlen(mem->labels[n]) - 1] = '\0' : 0;
    if (ft_strcmp(mem->labels[n], &word[2]) == 0 || ft_strcmp(mem->labels[n], &word[1]) == 0)
    {
      // printf("ICI%d\n", mem->i_label[n]);
      ret = mem->i_label[n] - where;
      break;
    }
    n++;
  }
  return (ret);
}

void ft_add_label(t_mem *mem,  char *str)
{
  int n;
  char **tmp;

  n = 0;
  tmp = (char **)malloc(sizeof(char *) * (mem->n_label + 2));
  while (n < mem->n_label)
  {
    tmp[n] = ft_strdup(mem->labels[n]);
    free(mem->labels[n]);
    n++;
  }
  free(mem->labels);
  tmp[n] = ft_strdup(str);
  tmp[n][ft_strlen(tmp[n]) - 1] = '\0';
  tmp[n + 1] = NULL;
  //mem->i_label = (int *)realloc(mem->i_label, mem->n_label + 1);
  mem->labels = tmp;
  // mem->labels[mem->n_label + 1] = NULL;
  //mem->i_label[mem->n_label] = mem->i;
  mem->n_label++;
}

/*
**    int       *where_used_label;
**    char      **used_label;
**    int       *size_used_label;
*/

void  ft_stock_label(char *word, t_mem *mem, int size, int add)
{
  int size_tab;
  char **tmp;
  int *tmp_where;
  int *tmp_write;
  int *tmp_size;
  int *tmp_add;
  int n;

  size_tab = 0;
  while (mem->used_label && mem->used_label[size_tab] != NULL)
    size_tab++;
  // printf("word = %s\n", word);
  tmp = (char **)malloc(sizeof(char *) * (size_tab + 2));
  tmp_where = (int *)malloc(sizeof(int) * (size_tab + 1));
  tmp_size = (int *)malloc(sizeof(int) * (size_tab + 1));
  tmp_write = (int *)malloc(sizeof(int) * (size_tab + 1));
  tmp_add = (int *)malloc(sizeof(int) * (size_tab + 1));
  n = 0;
  while (n < size_tab)
  {
    tmp[n] = ft_strdup(mem->used_label[n]);
    tmp_where[n] = mem->where_used_label[n];
    tmp_size[n] = mem->size_used_label[n];
    tmp_write[n] = mem->where_write_label[n];
    tmp_add[n] = mem->to_add[n];
    free(mem->used_label[n]);
    n++;
  }
  free(mem->used_label);
  free(mem->where_used_label);
  free(mem->size_used_label);
  free(mem->where_write_label);
  tmp[n] = ft_strdup(word);
  tmp[n + 1] = NULL;
  // printf("meme->i %d\n", mem->i);
  tmp_write[n] = mem->i;
  tmp_where[n] = mem->where;
  tmp_size[n] = size;
  tmp_add[n] = add;
  mem->used_label = tmp;
  mem->where_used_label = tmp_where;
  mem->size_used_label = tmp_size;
  mem->where_write_label = tmp_write;
  mem->to_add = tmp_add;
}

int   ft_fill_mem(int n, int i, char *word, t_mem *mem)
{
  int size;
  int ins;

  // printf("word : %s  word[0] : %c\n", word, word[0]);
  if (word[0] == DIRECT_CHAR)
  {
    if ((op_tab[i - 1].possible_param[n - 1] & T_DIR) != T_DIR)
    {
      ft_exit("Error : Bad possible_param : |%s|\n", -1, mem);
      return (0);
    }
    size = (op_tab[i - 1].direct_size == 1) ? IND_SIZE : DIR_SIZE;
    if (!(mem->tmp = (char *)realloc(mem->tmp, mem->i + size)))
      return (0);
    mem->tmp[mem->i] = 0;
    // printf("word %s\n", word);
    if (ft_str_is_digit(&word[1]))
      ins = ft_atoi(&word[1]);
    else
    {
      if (word[ft_strlen(word) - 1] == '\n')
        word[ft_strlen(word) - 1] = '\0';
      ft_stock_label(word, mem, size, 0);
      ins = 0;
    }
    if (size == DIR_SIZE)
      *(int *)(mem->tmp + mem->i) = reverse_endian_int(ins);
    else
      *(short *)(mem->tmp + mem->i) = reverse_endian_short((short)ins);
    (mem->i) += size;
    // printf("word : %s  word[0] : %c\n", word, word[0]);
    // printf("op_tab[i - 1].direct_size =%d, size = %d\n",op_tab[i - 1].direct_size, size);
    return (DIR_CODE);
  }
  else if (word[0] == REGISTER_CHAR)
  {
    if ((op_tab[i - 1].possible_param[n - 1] & T_REG) != T_REG)
    {
      ft_exit("Error : Bad possible_param : |%s|\n", -1, mem);
      return (0);
    }
    size = 1;
    if (!(mem->tmp = (char *)realloc(mem->tmp, mem->i + size)))
      return (0);
    mem->tmp[mem->i] = ft_atoi(&word[1]);
    (mem->i) += size;
    return (REG_CODE);
  }
  else
  {
    // printf("word : %s  word[0] : %c\n", word, word[0]);
    if ((op_tab[i - 1].possible_param[n - 1] & T_IND) != T_IND)
    {
      ft_exit("Error : Bad possible_param : |%s|\n", -1, mem);
      return (0);
    }
    size = IND_SIZE;
    //printf("%s\n", word);
    //printf("%d %d\n", (short)ft_atoi(&word[0]), reverse_endian_short((short)ft_atoi(&word[0])));
    if (word[0] == ':')
    {
      // printf("word : %s  word[0] : %c\n", word, word[0]);
      if (word[ft_strlen(word) - 1] == '\n')
        word[ft_strlen(word) - 1] = '\0';
      if (ft_strchr(word, '+') != NULL || ft_strchr(word, '-') != NULL)
        ft_exit("Error +|-", -1, mem);
      // if (ft_strchr(word, '+') != NULL)
      //   ft_stock_label(word, mem, size, ft_atoi(ft_strchr(word, '+')));
      // if (ft_strchr(word, '-') != NULL)
      //   ft_stock_label(word, mem, size, ft_atoi(ft_strchr(word, '-')));
      else
        ft_stock_label(word, mem, size, 0);
      ins = 0;
    }
    if (!(mem->tmp = (char *)realloc(mem->tmp, mem->i + size)))
      return (0);
    *(short *)(mem->tmp + mem->i) = reverse_endian_short((short)ft_atoi(&word[0]));
    (mem->i) += size;
    return (IND_CODE);
  }
}

/*
**  ft_mem_instr(int i, char *word, t_mem *mem)
**  store in t_mem mem.tmp the opcode of the instruction
**  i is the index of the instruction in op_tab
*/

int ft_mem_instr(int n, int i, char *word, t_mem *mem)
{
  int   size;

  if (ft_strcmp(op_tab[i - 1].name, word) == 0)
  {
    mem->where = mem->i + 1;
    size = 1 + op_tab[i - 1].encoding_byte;
    if (!(mem->tmp = (char *)realloc(mem->tmp, mem->i + size)))
      return (0);
    // printf("%s : %x\n", word , op_tab[i - 1].opcode);
    mem->tmp[mem->i] = op_tab[i - 1].opcode;
    if (op_tab[i - 1].encoding_byte)
    {
      mem->enc_b_i = mem->i;
      mem->tmp[mem->i + 1] = 0;
    }
    else
      mem->enc_b_i = -1;
    (mem->i) += size;
    return (0);
  }
  else
    return (ft_fill_mem(n, i, word, mem));
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
    if ((*word)[n] == '\t' || (*word)[n] == SEPARATOR_CHAR)
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
  unsigned char enc_b;
  char *tmp;

  n = 0;
  enc_b = 0;
  while (word_in_line[n] != NULL)
  {
    tmp = ft_strrchr(word_in_line[n], COMMENT_CHAR);
    if (tmp != NULL)
    {
      tmp[0] = '\0';
      word_in_line[n + 1] = NULL;
    }
    if (word_in_line[n][0] == '\0' || word_in_line[n][0] == '\n')
    {
      word_in_line[n] = NULL;
      break;
    }
    // printf("%d |%s|\n", n, word_in_line[n]);
    enc_b += ft_mem_instr(n, i, word_in_line[n], mem);
    enc_b = enc_b << 2;
    n++;
  }
  enc_b = enc_b << (6 - ((n - 1) * 2));
  // printf("encoding_byte = %x\n", enc_b);
  if (mem->enc_b_i > -1)
  {
    // printf("%x\n", enc_b);
    mem->tmp[mem->enc_b_i + 1] = enc_b;
  }
  if (op_tab[i - 1].param_nb - (n - 1) != 0)
  {
    ft_exit("Mauvais nombre d'argument dans l'instruction\n", -1, mem);
    return (0);
  }
  return (1);
}

int   find_max_len(char *str)
{
  int i;
  int max_len;

  i = 0;
  max_len = 0;
  while (op_tab[i].name != NULL)
  {
    if (ft_strncmp(op_tab[i].name, str, ft_strlen(op_tab[i].name)) == 0 &&
    (ft_strlen(op_tab[i].name) > ft_strlen(op_tab[max_len - 1].name) || max_len == 0))
    {
      max_len = i + 1;
    }
    i++;
  }
  return (max_len);
}

char *add_space_direct_char(char *str)
{
  int n;
  int i;
  int max_len;

  n = 0;
  while (str && str[n] && (str[n] == ' ' || str[n] == '\t'))
    n++;
  max_len = find_max_len(&str[n]);
  n = n + ft_strlen(op_tab[max_len - 1].name);
  if (max_len && str[n] == '%')
  {
    i = ft_strlen(str) + 1;
    str = (char *)realloc(str, ft_strlen(str) + 2);
    while (i != n)
    {
      str[i] = str[i - 1];
      i--;
    }
    str[i] = ' ';
  }
  return (str);
}

char *remove_space_add_char(char *str)
{
  int n;
  int virgule;

  n = 0;
  virgule = 0;
  while (str[n] != '\0')
  {
    if (str[n] == ',')
      virgule = 1;
    if ((str[n] == '+' || str[n] == '-') && n > 0 && str[n - 1] == ' ' && virgule == 1)
    {
      while (str[n] != '\0')
      {
        str[n - 1] = str[n];
        n++;
      }
      n = -1;
    }
    n++;
  }
  return (str);
}

// void ft_del_mem(mem->labels)

void ft_label_place(t_mem *mem)
{
  int n;
  int *tmp;

  n = 0;
  tmp = (int *)malloc(sizeof(int) * (mem->n_label));
  while (n < mem->n_label - 1)
    {
      tmp[n] = mem->i_label[n];
      n++;
    }
  free(mem->i_label);
  tmp[n] = mem->i + 1;
  //mem->i_label = (int *)realloc(mem->i_label, mem->n_label + 1);
  mem->i_label = tmp;
  // mem->labels[mem->n_label + 1] = NULL;
  //mem->i_label[mem->n_label] = mem->i;
  // n = 0;
  // while (n < mem->n_label)
  // {
  //   printf("mem->n %d | mem->i_label[n] %d\n", n, mem->i_label[n]);
  //   n++;
  // }
  n = 0;
}

int   ft_str_is_label(char *str)
{
  if ((str[ft_strlen(str) - 1] == ':') || (str[ft_strlen(str) - 2] == ':' && str[ft_strlen(str) - 1] == '\n'))
    return (1);
  return (0);
}

/*
**    int       *where_used_label;
**    char      **used_label;
**    int       *size_used_label;
*/

void fill_label_in_mem(t_mem *mem)
{
  int n;
  int ins;

  n = 0;
  while (mem->used_label && mem->used_label[n])
  {
    // printf("%d |%s|\n", n, mem->used_label[n]);
    ins = ft_label_exist(mem->used_label[n], mem, mem->where_used_label[n] + mem->to_add[n]);
    // printf("%s %d %d %d %d %d\n", mem->used_label[n], mem->where_write_label[n], mem->where_used_label[n], mem->size_used_label[n], ins, mem->to_add[n]);
    // printf("%s %d %x %x %x\n", mem->used_label[n], mem->where_write_label[n], mem->where_used_label[n], mem->size_used_label[n], ins);
    // printf("%x %x\n", reverse_endian_int(ins), reverse_endian_short((short)ins));
    if (mem->size_used_label[n] == DIR_SIZE)
      *(int *)(mem->tmp + mem->where_write_label[n]) = reverse_endian_int(ins);
    else
      *(short *)(mem->tmp + mem->where_write_label[n]) = reverse_endian_short((short)ins);
    // printf("avant : %04X, apres : %04X\n", ins, reverse_endian_int(ins));
    n++;
  }
}

/*
**  unsigned int		magic;
**  char				    prog_name[PROG_NAME_LENGTH + 1];
**  unsigned int		prog_size;
**  char				    comment[COMMENT_LENGTH + 1];
*/

char  *ft_strrpl(char *dest, const char *src, char a, char b)
{
  int n;

  n = 0;
  while (src[n] != 0)
  {
    if (src[n] == a)
      dest[n] = b;
    else
      dest[n] = src[n];
    n++;
  }
  dest[n] = 0;
  return (dest);
}

int main(int ac, char const *av[])
{
  t_mem mem;
  char  **tmp;
  int   n = 0;
  int   fd;
  int   good;

  good = 0;
  ft_bzero(&mem, sizeof(mem));
  if (ac > 1)
  {
    fill_mem(&mem, av[1]);
    while (mem.data[n] != NULL)
    {
      mem.data[n] = ft_strrpl(mem.data[n], mem.data[n], ';', COMMENT_CHAR);
      mem.data[n] = add_space_direct_char(mem.data[n]);
      mem.data[n] = remove_space_add_char(mem.data[n]);
      tmp = ft_strsplit_2(mem.data[n], " \t,");
      // printf("#%d line: %s\ntmp[0] = %s\n", n, mem.data[n], tmp[0]);
      if (ft_strcmp(".comment", tmp[0]) == 0)
      {
        n = fill_header_comment(&mem, n);
        good++;
        // printf("%s\n", mem.header.comment);
      }
      else if (ft_strcmp(".name", tmp[0]) == 0)
      {
        good++;
        n = fill_header_name(&mem, n);
        // printf("%s\n", mem.header.prog_name);
      }
      else if (ft_str_is_label(tmp[0]))
      {
        // printf("%s\n", tmp[0]);
        ft_add_label(&mem, tmp[0]);
        ft_label_place(&mem);
        //printf("1 %s\n", mem.labels[mem.n_label - 1]);
      }
      else if (tmp[0][0] != COMMENT_CHAR && ft_str_in_op_tab(tmp[0]) == 0 && tmp[0][0] != '\0' && tmp[0][0] != ' ' && tmp[0][0] != '\n' && tmp[0][0] != '\t' && ft_strlen(tmp[0]) > 1)
      {
        ft_putnbr(n + 1);
        ft_putstr(" line : ");
        ft_putstr(tmp[0]);
        ft_exit("\nBad line", -1, &mem);
      }
      if (ft_str_in_op_tab(tmp[0]) != 0 || (tmp[1] && ft_str_in_op_tab(tmp[1]) != 0 && ft_str_is_label(tmp[0])))
      {
        if (good != 2)
          ft_exit("Missing comment or name", -1, &mem);
        if (ft_str_in_op_tab(tmp[0]) != 0)
          ft_instruction(ft_str_in_op_tab(tmp[0]), tmp, &mem);
        else
          ft_instruction(ft_str_in_op_tab(tmp[1]), &tmp[1], &mem);
        // if (mem.n_label)
          // printf("4 %s\n", mem.labels[0]);
        //printf("On a trouve l'instruction : %s (%d), en tant que 1er mot dans la ligne: %s\n", op_tab[i - 1].name, i, mem.data[n]);
      }
      ft_del_char_ptr(tmp);
      n++;
    }
    fill_label_in_mem(&mem);
    fd = create_new_cor(av[1]);
    mem.header.magic = reverse_endian_int(COREWAR_EXEC_MAGIC);
    mem.header.prog_size = reverse_endian_int(mem.i);
    write(fd, &mem.header, sizeof(mem.header));

    //printf("%d %s %d %s\n", mem.header.magic, mem.header.prog_name, mem.header.prog_size, mem.header.comment);
    write(fd, mem.tmp, mem.i);
  }
	return 0;
}
