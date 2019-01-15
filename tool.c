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
