# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmorais- <tmorais-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/10 10:15:16 by tmorais-          #+#    #+#              #
#    Updated: 2025/11/10 15:11:32 by tmorais-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= so_long
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f

MLX_DIR		= ./mlx
GNL_DIR		= ./gnl
SRC_DIR		= ./src
INC_DIR		= ./includes

MLX			= $(MLX_DIR)/libmlx.a
MLX_FLAGS	= -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

SRCS		= $(SRC_DIR)/main.c \
			  $(SRC_DIR)/map.c \
			  $(SRC_DIR)/map_utils.c \
			  $(SRC_DIR)/map_split.c \
			  $(SRC_DIR)/validate_paths.c \
			  $(SRC_DIR)/validate.c \
			  $(SRC_DIR)/validate_counts.c \
			  $(SRC_DIR)/flood_fill.c \
			  $(SRC_DIR)/hooks.c \
			  $(SRC_DIR)/player.c \
			  $(SRC_DIR)/render.c \
			  $(SRC_DIR)/utils2.c \
			  $(SRC_DIR)/utils.c

GNL_SRC 	= $(GNL_DIR)/get_next_line_bonus.c \
			  $(GNL_DIR)/get_next_line_utils_bonus.c

OBJS		= $(SRCS:.c=.o) $(GNL_SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(MLX)
	@echo "\033[0;32m[Compiling] $(NAME)...\033[0m"
	@$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME)
	@echo "\033[1;32m✅ Compiling successfully!\033[0m"

$(MLX):
	@$(MAKE) -C $(MLX_DIR)

%.o: %.c
	@$(CC) $(CFLAGS) -I$(INC_DIR) -I$(MLX_DIR) -I$(GNL_DIR) -c $< -o $@
	@echo "\033[0;36mCompiling:\033[0m $<"

clean:
	@$(RM) $(OBJS)
	@echo "\033[0;33m🧹 Objects removed.\033[0m"

fclean: clean
	@$(RM) $(NAME)
	@echo "\033[0;31m🗑️  Executable removed.\033[0m"

re: fclean all

run: all
	@./$(NAME) maps/mapa.ber

norm:
	@norminette $(SRC_DIR) $(INC_DIR) | grep -v "OK!" || true

.PHONY: all clean fclean re run norm
