NAME := minishell
HEADER := -ILibft/include -Iinclude
CC := cc
CFLAGS := -Wall -Wextra -Werror -g
RM := rm -rf
LIB := Libft/libft.a

FILES := main

SRC_DIR := src/
OBJ_DIR := obj/

OBJS = $(addsuffix .o, $(addprefix $(OBJ_DIR), $(FILES)))

all: $(NAME)

$(NAME): $(LIB) $(OBJS)
	$(CC) $(CFLAGS) $(HEADER) -o $@ $^

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(HEADER) -c $< -o $@

$(LIB):
	make -C Libft

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)
	make fclean -C Libft

re: fclean all

.PHONY: all, clean, fclean, re