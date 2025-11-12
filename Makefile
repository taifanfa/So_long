# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmfanfa <tmfanfa@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/11 13:00:00 by tmorais-          #+#    #+#              #
#    Updated: 2025/11/11 12:27:44 by tmfanfa          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ============================================================================ #
#                                  EXECUTABLES                                 #
# ============================================================================ #

NAME		= so_long
NAME_BONUS	= so_long_bonus

# ============================================================================ #
#                                  COMPILATION                                 #
# ============================================================================ #

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f

# ============================================================================ #
#                                  DIRECTORIES                                 #
# ============================================================================ #

MLX_DIR		= ./mlx
GNL_DIR		= ./gnl
SRC_DIR		= ./src
SRC_BONUS_DIR = ./src_bonus
INC_DIR		= ./includes

# ============================================================================ #
#                                    LIBRARIES                                 #
# ============================================================================ #

MLX			= $(MLX_DIR)/libmlx.a
MLX_FLAGS	= -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# ============================================================================ #
#                              MANDATORY SOURCE FILES                          #
# ============================================================================ #

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
			  $(SRC_DIR)/utils.c \
			  $(SRC_DIR)/utils2.c

GNL_SRC		= $(GNL_DIR)/get_next_line_bonus.c \
			  $(GNL_DIR)/get_next_line_utils_bonus.c

OBJS		= $(SRCS:.c=.o) $(GNL_SRC:.c=.o)

# ============================================================================ #
#                               BONUS SOURCE FILES                             #
# ============================================================================ #

SRCS_BONUS	= $(SRC_BONUS_DIR)/main_bonus.c \
			  $(SRC_BONUS_DIR)/map_bonus.c \
			  $(SRC_BONUS_DIR)/map_utils_bonus.c \
			  $(SRC_BONUS_DIR)/map_split_bonus.c \
			  $(SRC_BONUS_DIR)/validate_paths_bonus.c \
			  $(SRC_BONUS_DIR)/validate_bonus.c \
			  $(SRC_BONUS_DIR)/validate_counts_bonus.c \
			  $(SRC_BONUS_DIR)/flood_fill_bonus.c \
			  $(SRC_BONUS_DIR)/hooks_bonus.c \
			  $(SRC_BONUS_DIR)/player_bonus.c \
			  $(SRC_BONUS_DIR)/render_bonus.c \
			  $(SRC_BONUS_DIR)/utils_bonus.c \
			  $(SRC_BONUS_DIR)/utils2_bonus.c \
			  $(SRC_BONUS_DIR)/animation_bonus.c \
			  $(SRC_BONUS_DIR)/enemy_bonus.c \
			  $(SRC_BONUS_DIR)/ft_itoa_bonus.c \
			  $(SRC_BONUS_DIR)/ft_strjoin_bonus.c

OBJS_BONUS	= $(SRCS_BONUS:.c=.o) $(GNL_SRC:.c=.o)

# ============================================================================ #
#                                     COLORS                                   #
# ============================================================================ #

GREEN		= \033[0;32m
YELLOW		= \033[0;33m
RED			= \033[0;31m
BLUE		= \033[0;34m
CYAN		= \033[0;36m
MAGENTA		= \033[0;35m
RESET		= \033[0m
BOLD		= \033[1m

# ============================================================================ #
#                                     RULES                                    #
# ============================================================================ #

all: $(NAME)

$(NAME): $(OBJS) $(MLX)
	@echo "$(CYAN)━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━$(RESET)"
	@echo "$(BOLD)$(GREEN)[Linking] $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME)
	@echo "$(BOLD)$(GREEN)✅ $(NAME) compiled successfully!$(RESET)"
	@echo "$(CYAN)━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━$(RESET)"

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS) $(MLX)
	@echo "$(MAGENTA)━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━$(RESET)"
	@echo "$(BOLD)$(MAGENTA)[Linking BONUS] $(NAME_BONUS)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS_BONUS) $(MLX_FLAGS) -o $(NAME_BONUS)
	@echo "$(BOLD)$(MAGENTA)✅ $(NAME_BONUS) compiled successfully!$(RESET)"
	@echo "$(MAGENTA)━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━$(RESET)"

$(MLX):
	@echo "$(YELLOW)[Building] MLX library...$(RESET)"
	@$(MAKE) -C $(MLX_DIR) --no-print-directory
	@echo "$(GREEN)✅ MLX library built!$(RESET)"

# Regra para compilar objetos do mandatório
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -I$(INC_DIR) -I$(MLX_DIR) -I$(GNL_DIR) -c $< -o $@
	@echo "$(CYAN)[Compiling]$(RESET) $<"

# Regra para compilar objetos do bônus
$(SRC_BONUS_DIR)/%.o: $(SRC_BONUS_DIR)/%.c
	@$(CC) $(CFLAGS) -I$(INC_DIR) -I$(MLX_DIR) -I$(GNL_DIR) -c $< -o $@
	@echo "$(MAGENTA)[Compiling BONUS]$(RESET) $<"

# Regra para compilar GNL
$(GNL_DIR)/%.o: $(GNL_DIR)/%.c
	@$(CC) $(CFLAGS) -I$(GNL_DIR) -c $< -o $@
	@echo "$(BLUE)[Compiling GNL]$(RESET) $<"

clean:
	@$(RM) $(OBJS) $(OBJS_BONUS)
	@echo "$(YELLOW)🧹 Object files removed.$(RESET)"

fclean: clean
	@$(RM) $(NAME) $(NAME_BONUS)
	@echo "$(RED)🗑️  Executables removed.$(RESET)"

re: fclean all

re_bonus: fclean bonus

# ============================================================================ #
#                                  UTILITY RULES                               #
# ============================================================================ #

run: all
	@echo "$(GREEN)━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━$(RESET)"
	@echo "$(BOLD)$(GREEN)🎮 Running $(NAME)...$(RESET)"
	@echo "$(GREEN)━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━$(RESET)"
	@./$(NAME) maps/mapa.ber

run_bonus: bonus
	@echo "$(MAGENTA)━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━$(RESET)"
	@echo "$(BOLD)$(MAGENTA)🎮 Running $(NAME_BONUS)...$(RESET)"
	@echo "$(MAGENTA)━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━$(RESET)"
	@./$(NAME_BONUS) maps/bonus_simple.ber

norm:
	@echo "$(BLUE)━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━$(RESET)"
	@echo "$(BOLD)$(BLUE)📋 Norminette Check$(RESET)"
	@echo "$(BLUE)━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━$(RESET)"
	@norminette $(SRC_DIR) $(SRC_BONUS_DIR) $(INC_DIR) $(GNL_DIR) | grep -v "OK!" || echo "$(GREEN)✅ All files OK!$(RESET)"

# Testa vários mapas
test: all
	@echo "$(CYAN)━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━$(RESET)"
	@echo "$(BOLD)$(CYAN)🧪 Testing maps...$(RESET)"
	@echo "$(CYAN)━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━$(RESET)"
	@for map in maps/*.ber; do \
		echo "$(YELLOW)Testing: $$map$(RESET)"; \
		./$(NAME) $$map || true; \
	done

test_bonus: bonus
	@echo "$(MAGENTA)━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━$(RESET)"
	@echo "$(BOLD)$(MAGENTA)🧪 Testing bonus maps...$(RESET)"
	@echo "$(MAGENTA)━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━$(RESET)"
	@for map in maps/bonus*.ber; do \
		echo "$(YELLOW)Testing: $$map$(RESET)"; \
		./$(NAME_BONUS) $$map || true; \
	done

# Valgrind para detectar leaks
valgrind: all
	@echo "$(RED)━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━$(RESET)"
	@echo "$(BOLD)$(RED)🔍 Running Valgrind...$(RESET)"
	@echo "$(RED)━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━$(RESET)"
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
		./$(NAME) maps/mapa.ber

valgrind_bonus: bonus
	@echo "$(RED)━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━$(RESET)"
	@echo "$(BOLD)$(RED)🔍 Running Valgrind on BONUS...$(RESET)"
	@echo "$(RED)━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━$(RESET)"
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
		./$(NAME_BONUS) maps/bonus_simple.ber

help:
	@echo "$(BLUE)━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━$(RESET)"
	@echo "$(BOLD)$(CYAN)📖 So_long Makefile Commands$(RESET)"
	@echo "$(BLUE)━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━$(RESET)"
	@echo "$(GREEN)make$(RESET)              - Compile mandatory"
	@echo "$(MAGENTA)make bonus$(RESET)        - Compile bonus"
	@echo "$(YELLOW)make clean$(RESET)        - Remove object files"
	@echo "$(RED)make fclean$(RESET)       - Remove objects and executables"
	@echo "$(CYAN)make re$(RESET)           - Recompile mandatory"
	@echo "$(MAGENTA)make re_bonus$(RESET)     - Recompile bonus"
	@echo "$(GREEN)make run$(RESET)          - Compile and run mandatory"
	@echo "$(MAGENTA)make run_bonus$(RESET)    - Compile and run bonus"
	@echo "$(BLUE)make norm$(RESET)         - Check norminette"
	@echo "$(CYAN)make test$(RESET)         - Test all maps (mandatory)"
	@echo "$(MAGENTA)make test_bonus$(RESET)   - Test all bonus maps"
	@echo "$(RED)make valgrind$(RESET)     - Run with valgrind (mandatory)"
	@echo "$(RED)make valgrind_bonus$(RESET) - Run with valgrind (bonus)"
	@echo "$(BLUE)make help$(RESET)         - Show this help"
	@echo "$(BLUE)━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━$(RESET)"

.PHONY: all bonus clean fclean re re_bonus run run_bonus norm test test_bonus \
		valgrind valgrind_bonus help
