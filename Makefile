NAME := minishell
HEADER := -Ilibft/include -Iinclude
LFLAGS := -lreadline
CC := cc
CFLAGS = -Wall -Wextra -Werror -g
RM := rm -rf
LIB := libft/libft.a

SRC_DIR := src/
SRCS := $(shell find $(SRC_DIR) -name "*.c")

OBJ_DIR := obj/
OBJS := $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRCS))

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