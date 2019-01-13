#include <stdlib.h>
#include "libft/libft.h"
#include "op.h"

void	ft_freetab(char **tab)
{
	int	i;

	i = 0;
	if (tab == NULL)
		return ;
	while (tab[i] != NULL)
	{
		ft_strdel(&tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
}

void	ft_exit(char *exit_msg, int status, t_mem *mem)
{
    free(mem->file);
    ft_freetab(mem->data);
    free(mem->tmp);
    ft_freetab(mem->labels);
    free(mem->i_label);
    free(mem->where_used_label);
    free(mem->where_write_label);
    ft_freetab(mem->used_label);
    free(mem->size_used_label);
	if (exit_msg != NULL)
		ft_putendl(exit_msg);
	exit(status);
}
