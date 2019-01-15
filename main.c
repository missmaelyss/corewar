#include "op.h"

/*
**  unsigned int		magic;
**  char				    prog_name[PROG_NAME_LENGTH + 1];
**  unsigned int		prog_size;
**  char				    comment[COMMENT_LENGTH + 1];
*/

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
        ft_putstr("Lexical error at [");
        ft_putnbr(n + 1);
        ft_putstr(":1");
        ft_exit("]", -1, &mem);
      }
      if (ft_str_in_op_tab(tmp[0]) != 0 || (tmp[1] && ft_str_in_op_tab(tmp[1]) != 0 && ft_str_is_label(tmp[0])))
      {
        if (good != 2)
          ft_exit("Missing comment or name", -1, &mem);
        if (ft_str_in_op_tab(tmp[0]) != 0)
        {  if (ft_instruction(ft_str_in_op_tab(tmp[0]), tmp, &mem) == -1)
                  {
                    ft_putstr("Lexical error at [");
                    ft_putnbr(n + 1);
                    ft_putstr(":1");
                    ft_exit("]", -1, &mem);
                  }}
        else
        {  if (ft_instruction(ft_str_in_op_tab(tmp[1]), &tmp[1], &mem) == -1)
                  {
                    ft_putstr("Lexical error at [");
                    ft_putnbr(n + 1);
                    ft_putstr(":2");
                    ft_exit("]", -1, &mem);
                  }}
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
