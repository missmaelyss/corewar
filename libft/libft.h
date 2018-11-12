/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marnaud <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 10:02:11 by marnaud           #+#    #+#             */
/*   Updated: 2017/01/24 18:28:17 by marnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H

# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

int					get_next_line(int fd, char **line);
int					ft_toupper(int c);
int					ft_tolower(int c);
char				*ft_strtrim(char const *s);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strstr(const char *meule_de_foin, const char *aiguille);
char				**ft_strsplit(char const *s, char c);
char				*ft_strrchr(const char *s, char c);
char				*ft_strnstr(const char *meule_de_foin,
		const char *aiguille, size_t i);
char				*ft_strnew(size_t size);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strncpy(char *dest, const char *src, size_t n);
int					ft_strncmp(const char *s1, const char *s2, size_t l);
char				*ft_strncat(char *dest, const char *src, size_t n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strmap(char const *s, char (*f)(char));
size_t				ft_strlen(const char *str);
size_t				ft_strlcat(char *dest, const char *src, size_t l);
char				*ft_strjoin(char const *s1, char const *s2);
void				ft_striteri(char *s, void(*f)(unsigned int, char *));
void				ft_striter(char *s, void (*f)(char*));
void				ft_strdel(char **as);
char				*ft_strcpy(char *dest, const char *src);
int					ft_strcmp(const char *s1, const char *s2);
void				ft_strclr(char *s);
char				*ft_strchr(const char *s, char c);
char				*ft_strcat(char *dest, const char *src);
void				ft_putchar_fd(char c, int fd);
void				ft_putchar(char c);
void				ft_putnbr_fd(int n, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putnbr(int n);
void				ft_putendl(char const *s);
void				ft_putstr(char const *s);
char				*ft_itoa(int n);
int					ft_strequ(char const *s1, char const *s2);
void				ft_memdel(void **ap);
void				*ft_memalloc(size_t size);
int					ft_isprint(int c);
int					ft_isascii(int c);
int					ft_isalnum(int a);
int					ft_isdigit(int a);
int					ft_isalpha(int a);
int					ft_atoi(const char *str);
char				*ft_strdup(const char *str);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memccpy(void *dest, const void *src, int c, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_memset(void *str, int c, size_t n);
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
char				*ft_convert_base(char *nbr, char *base_from, char *base_to);
int					ft_find_next_prime(int nb);
int					ft_recursive_factorial(int nb);
int					ft_recursive_power(int nb, int power);
int					ft_ultimate_range(int **range, int min, int max);

#endif
