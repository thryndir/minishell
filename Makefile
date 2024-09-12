NAME := minishell
HEADER := -Ilib/libft/include -Iinclude
CC := cc
CFLAGS := -Wall -Wextra -Werror -g
RM := rm -rf
LIB := lib/libft/libft.a

FILES := executing/main parsing/main

SRC_DIR := src/
OBJ_DIR := obj/

SRCS := $(addprefix src/, $(addsuffix .c, $(FILES)))
OBJS := $(addprefix obj/, $(addsuffix .o, $(FILES)))

all: $(NAME)

$(NAME): $(OBJ_DIR) $(LIB) $(OBJS)
	$(CC) $(CFLAGS) $(HEADER) $(LIB) -o $@

$(OBJ_DIR):
	@mkdir -p $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) $(HEADER) -c $< -o $@

$(LIB):
	make -C lib/libft

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)
	make fclean -C lib/libft

re: fclean all

.PHONY: all, clean, fclean, re