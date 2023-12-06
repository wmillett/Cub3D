NAME = cub3D

INCLUDES = -I ./libft/ -I ./MLX42/include/MLX42/ -I ./
SRC = ""

LIBFT = libft/libft.a
LIBMLX = $(MLX_DIR)libmlx42.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror
MLXFL = -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/" -framework Cocoa -framework OpenGL -framework IOKit #-fsanitize=address -g
RM = rm -f

MLX42 = ./MLX42/
LIBFT_DIR = ./libft/
MLX_DIR = ./MLX42/build/

CYAN = '\033[1;36m'
RED = '\033[0;31m'
RESET_COLOR = '\033[0;0m'

all: $(NAME)

$(NAME):  $(MLX42) $(SRC) $(LIBFT)
	@make -C $(MLX_DIR)
	@$(CC) $(CFLAGS) $(SRC) $(LIBMLX) $(LIBFT) $(MLXFL) $(INCLUDES) -o $(NAME)
	@ echo $(CYAN) cub3D created! $(RESET_COLOR)

$(MLX42):
	git clone https://github.com/codam-coding-college/MLX42.git ./MLX42
	@(cd ./MLX42 && cmake -B build && cmake --build build -j4)

$(LIBFT): 
	@$(MAKE) -C $(LIBFT_DIR)
				
clean: 
	@$(MAKE) clean -C $(LIBFT_DIR)
	@echo $(RED) object files deleted! 🗑️ $(RESET_COLOR)

mlx_clean:
	@if [ -d "$(MLX42)" ]; then \
		make -C $(MLX_DIR) clean; \
	fi
	
fclean: clean
	@$(MAKE) mlx_clean
	@$(RM) $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR)
	@echo $(RED) cub3D,libft.a and mlx files deleted! 🗑️ $(RESET_COLOR)

re: fclean all

.PHONY: all clean fclean re