# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgalloux <lgalloux@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/29 18:19:52 by lgalloux          #+#    #+#              #
#    Updated: 2024/09/17 14:12:00 by lgalloux         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -rf
HEADER = -Iinclude -I../include
NAME = libft.a
TNAME = test

FILES = libft/ft_strlen libft/ft_isprint libft/ft_isalnum\
libft/ft_isalpha libft/ft_isdigit libft/ft_memset libft/ft_isascii libft/ft_bzero\
libft/ft_memcpy libft/ft_memmove libft/ft_strlcpy libft/ft_strlcat libft/ft_toupper\
libft/ft_tolower libft/ft_strchr libft/ft_strrchr libft/ft_strncmp libft/ft_memchr\
libft/ft_memcmp libft/ft_strnstr libft/ft_atolli libft/ft_calloc libft/ft_strdup\
libft/ft_substr libft/ft_strjoin libft/ft_strtrim libft/ft_split libft/ft_itoa\
libft/ft_strmapi libft/ft_striteri libft/ft_putchar_fd libft/ft_putstr_fd\
libft/ft_putendl_fd libft/ft_putnbr_fd libft/ft_lstsize libft/ft_lstlast\
libft/ft_lstnew libft/ft_lstadd_front libft/ft_lstadd_back libft/ft_atoull\
libft/ft_lstdelone libft/ft_lstclear libft/ft_lstiter libft/ft_lstmap libft/ft_putnbr\
libft/ft_is_word_in libft/ft_isspace libft/ft_strcmp\
printf/ft_gestchar printf/ft_gesthexa printf/ft_gestint printf/ft_printf\
gnl/get_next_line gnl/get_next_line_utils

SRC_DIR = src/
OBJ_DIR = obj/

SRCS = $(addsuffix .c, $(addprefix $(SRC_DIR), $(FILES)))
OBJS = $(addsuffix .o, $(addprefix $(OBJ_DIR), $(FILES)))

all: $(NAME)

$(NAME): $(OBJS)
	ar rc $@ $^

$(TNAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $(HEADER) $(CFLAGS) -o $@ -c $<

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME) $(TNAME)

re: fclean all

.PHONY: all clean fclean re
