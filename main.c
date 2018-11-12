#include "libft/libft.h"
#include "op.h"

int main(int ac, char const *av[])
{
  int n;

  if (ac > 1)
  {
    ft_putstr(av[1]);
    ft_putstr("\n");
  }
  n = 0;
  while (op_tab[n].name != 0)
  {
    ft_putstr(op_tab[n].name);
    ft_putstr("\n");
    n++;
  }
	return 0;
}
