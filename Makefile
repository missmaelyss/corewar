NAME = asm

CC = gcc

LDFLAGS=

CFLAGS = -Wall -Wextra -Werror -g 

LIBFT = libft/libft.a

SRC_NAME = main.c fill_mem.c start.c op.c ft_str_split_2.c ft_str_split_3.c error.c tool.c other_tool.c instruction.c create_label.c handle_label.c

OBJ_PATH = obj/

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC_PATH = src/

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))

OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))

all : $(NAME)

$(NAME) : $(LIBFT) $(OBJ_PATH) $(OBJ)
	@echo ""
	@$(CC) $(OBJ) $(LIBFT) -o $@ 
	@echo "\x1b[32;01m$(NAME) SUCCESSFULLY CREATED !\x1b[32;00m"

$(OBJ_PATH):
	@mkdir -p $@

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@echo "\x1b[32;01m.\x1b[32;00m\c"
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $<

$(LIBFT) :
	@(cd libft && $(MAKE))
	@echo "\033[32mLibrairies compiled\033[0m"

.PHONY : all clean fclean re

clean :
	@(cd libft && $(MAKE) $@)
	@rm -rf $(OBJ)
	@rm -rf $(OBJ_PATH)
	@echo "\033[32mObjects deleted\nLibraries cleaned\033[0m"

fclean : clean
	@(cd libft && $(MAKE) $@)
	@rm -rf $(NAME)
	@echo "\033[32m$(NAME) deleted\033[0m"

re : fclean all
