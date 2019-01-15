
int   ft_str_is_label(char *str)
{
  if ((str[ft_strlen(str) - 1] == ':') || (str[ft_strlen(str) - 2] == ':' && str[ft_strlen(str) - 1] == '\n'))
    return (1);
  return (0);
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