# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nbrucker <nbrucker@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/02 19:25:43 by nbrucker          #+#    #+#              #
#    Updated: 2019/01/18 18:37:16 by qduperon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

INCSDIR = includes/

SRCSDIR = srcs/

OBJSDIR = objs/

SRCS = ft_memset.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memccpy.c \
		ft_memmove.c \
		ft_strlen.c \
		ft_strdup.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_atoi.c \
		ft_strcpy.c \
		ft_strncpy.c \
		ft_strcat.c \
		ft_strncat.c \
		ft_strlcat.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strstr.c \
		ft_strnstr.c \
		ft_strcmp.c \
		ft_strncmp.c \
		ft_isalpha.c \
		ft_isupper.c \
		ft_islower.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_memalloc.c \
		ft_memdel.c \
		ft_strnew.c \
		ft_strdel.c \
		ft_strclr.c \
		ft_striter.c \
		ft_striteri.c \
		ft_strmap.c \
		ft_strmapi.c \
		ft_strequ.c \
		ft_strnequ.c \
		ft_strsub.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_strsplit.c \
		ft_itoa.c \
		ft_putchar.c \
		ft_putstr.c \
		ft_putendl.c \
		ft_putnbr.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_lstnew.c \
		ft_lstdelone.c \
		ft_lstdel.c \
		ft_lstadd.c \
		ft_lstiter.c \
		ft_lstmap.c \
		ft_remove_char.c \
		ft_remove_str.c \
		ft_char_index.c \
		ft_str_index.c \
		ft_int_index.c \
		ft_strstr_index.c \
		ft_putwchar.c \
		ft_putwchar_fd.c \
		ft_putwstr.c \
		ft_putwstr_fd.c \
		ft_error.c \
		get_next_line.c \
		ft_printf.c \
		ft_print.c \
		ft_pointers.c \
		ft_length.c \
		ft_flag.c \
		ft_flag_next.c \
		ft_handle_s.c \
		ft_unicode.c \
		ft_handle_us.c \
		ft_handle_flag.c \
		ft_handle_p.c \
		ft_handle_d.c \
		ft_handle_o.c \
		ft_handle_u.c \
		ft_handle_x.c \
		ft_handle_c.c \
		ft_handle_b.c \
		ft_handle_undefined.c \
		ft_handle_star.c \
		ft_handle_n.c \
		ft_handle_buffer.c \
		ft_color.c\
		ft_atoll.c\
		ft_strksplit.c\
		ft_strndup.c\
		ft_isblank.c\
		ft_strjoin_free.c

OBJS = $(addprefix $(OBJSDIR),$(SRCS:.c=.o))

$(OBJSDIR)%.o: $(SRCSDIR)%.c
	@mkdir -p $(OBJSDIR)
	$(CC) $(CFLAGS) -I $(INCSDIR) -o $@ -c $<

CC = gcc

CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

clean:
	rm -rf $(OBJSDIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
