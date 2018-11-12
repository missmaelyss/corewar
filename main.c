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

int main(int ac, char const *av[])
{
  header_t  header;
  int n;
  int i;
  int fd;
  int new_fd;
  char *line;

  header.magic = COREWAR_EXEC_MAGIC;
  if (ac > 1)
  {
    new_fd = create_new_cor(av[1]);
    printf("%d\n", new_fd);
    //printf("%zd\n", write(new_fd, header.prog_name, (2180)));
    if (new_fd != 0)
    {
      fd = open(av[1], O_RDONLY);
      n = 1;
      while (get_next_line(fd, &line) > 0)
    	{
          //printf("%s\n", line);
          if (ft_strchrword(line, NAME_CMD_STRING) == 1)
    		    printf("ligne %d : %s\n", n, line);
          if (ft_strchrword(line, COMMENT_CMD_STRING) == 1)
              printf("ligne %d : %s\n", n, line);
          i = 0;
          while (op_tab[i].name != 0)
          {
              if (ft_strchrword(line,op_tab[i].name) == 1)
                  printf("   ligne %d : %s %s\n", n, line, op_tab[i].name);
              i++;
          }
          n++;
    	}
    }
  }
	return 0;
}
