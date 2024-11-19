NAME := minishell
HEADER := -Ilibft/include -Iinclude
LFLAGS := -lreadline
CC := cc
CFLAGS = -Wall -Wextra -Werror -g
RM := rm -rf
LIB := libft/libft.a

FILES := main executing/browse executing/exec\
built_ins/echo built_ins/exec_builtins executing/init_exec\
built_ins/cd built_ins/env built_ins/exit built_ins/export built_ins/pwd\
built_ins/unset env/env_init env/env_management\
garbage_collector/gc_malloc garbage_collector/gc_malloc_utils\
utils/child_utils utils/memory_manage utils/strsjoin utils/error\
utils/utils

SRC_DIR := src/
OBJ_DIR := obj/

OBJS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(FILES)))

all: $(NAME)

$(NAME): $(OBJS) $(LIB)
	$(CC) $(CFLAGS) $^ $(LFLAGS) -o $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(HEADER) -o $@ -c $<

$(LIB):
	make -C libft

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re