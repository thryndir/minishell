# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/17 12:34:33 by lgalloux          #+#    #+#              #
#    Updated: 2024/09/17 15:47:24 by lgalloux         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell
HEADER := -Ilibft/include -Iinclude 
CC := cc
CFLAGS := -Wall -Wextra -Werror -g
RM := rm -rf
LIB := libft/libft.a 

FILES := main executing/init executing/init_exec executing/exec\
executing/utils executing/error built_ins/echo

SRC_DIR := src/
OBJ_DIR := obj/

OBJS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(FILES)))

all: $(NAME)

$(NAME): $(OBJS) $(LIB)
	$(CC) $(CFLAGS) $^ -o $@

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

.PHONY: all, clean, fclean, re
