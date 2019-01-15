

NAME = asm
CC = gcc
LDFLAGS=
CFLAGS = -Wall -Wextra -Werror -g
LIBFT = libft/libft.a
OBJDIR = obj
OBJ = $(SRC:%.c=$(OBJDIR)/%.o)
SRC = main.c fill_mem.c start.c op.c ft_str_split_2.c ft_str_split_3.c error.c tool.c other_tool.c instruction.c create_label.c handle_label.c

all : $(NAME)

$(NAME) : $(LIBFT) $(OBJ)
	@echo ""
	$(CC) -o $@ $^ $(LDFLAGS)
	@echo "\x1b[32;01m$(NAME) SUCCESSFULLY CREATED !\x1b[32;00m"

$(OBJDIR)/%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)
	@echo "\x1b[32;01m.\x1b[32;00m\c"

$(LIBFT) :
	@(cd libft && $(MAKE))
	@echo "\033[32mLibrairies compiled\033[0m"

.PHONY : all clean fclean re

clean :
	@(cd libft && $(MAKE) $@)
	@rm -rf $(OBJ)
	@echo "\033[32mObjects deleted\nLibraries cleaned\033[0m"

fclean : clean
	@(cd libft && $(MAKE) $@)
	@rm -rf $(NAME)
	@echo "\033[32m$(NAME) deleted\033[0m"

re : fclean all
