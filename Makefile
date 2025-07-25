# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jjakupi <marvin@42lausanne.ch>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/05 17:29:03 by julrusse          #+#    #+#              #
#    Updated: 2025/07/25 14:07:20 by jjakupi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= miniRT

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -O3
RM			= rm -rf

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

MLX_DIR		= minilibx-linux
MLX			= $(MLX_DIR)/libmlx.a

INC_DIR		= include
INCLUDES	= -I $(INC_DIR) -I $(LIBFT_DIR) -I $(MLX_DIR)

SRC_DIR		= sources
SRC			= $(shell find $(SRC_DIR) -type f -name '*.c')

OBJ_DIR		= $(SRC_DIR)/obj
OBJ			= $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

all: $(LIBFT) $(MLX) $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	@$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) \
		-L$(LIBFT_DIR) -lft \
		-L$(MLX_DIR) -lmlx \
		-lm -lXext -lX11 \
		-o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@$(RM) $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(MLX_DIR) clean

re: fclean all

.PHONY: all clean fclean re
