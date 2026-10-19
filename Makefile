# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mluvisot <mluvisot@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/10/19 12:45:00 by mluvisot          #+#    #+#              #
#    Updated: 2026/10/19 14:46:52 by mluvisot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= push_swap

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g
INCLUDES	= -I includes -I $(LIBFT_DIR)

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

SRC_DIR		= src
OBJ_DIR		= obj

SRCS		= main.c \
			$(SRC_DIR)/utils/utils.c \
			$(SRC_DIR)/utils/parse.c \
			$(SRC_DIR)/utils/push_swap.c \
			$(SRC_DIR)/operations/compute_dsorder.c \
			$(SRC_DIR)/operations/operation_swap.c \
			$(SRC_DIR)/operations/operation_push.c \
			$(SRC_DIR)/operations/operations_rotate.c \
			$(SRC_DIR)/operations/operations_reverse_rotate.c \
			$(SRC_DIR)/algo/algorithme_simple.c \
			$(SRC_DIR)/algo/algorithme_moyen.c \
			$(SRC_DIR)/algo/algorithme_complex.c

OBJS		= $(SRCS:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: %.c includes/push_swap.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
