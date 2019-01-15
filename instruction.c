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
      {
        return (-1);
        ft_putstr("Lexical error at [");
        ft_putnbr(n + 1);
        ft_exit("]", -1, mem);
        // ft_exit("Error +|-", -1, mem);
      }
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
**  int   ft_instruction(int i, char **word_in_line, t_mem *mem)
**  for now, this function is a way to cross a string word by words
**  checking if the nb of argument after the instruction is the same as
**  in op_tab
*/

int   ft_instruction(int i, char **word_in_line, t_mem *mem)
{
  int   n;
  unsigned char enc_b;
  char  *tmp;
  int   tmp2;

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
    if ((tmp2 = ft_mem_instr(n, i, word_in_line[n], mem)) == -1)
      return (-1);
    enc_b += tmp2;
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