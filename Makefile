NAME		= cub3d
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -Iinc -Ilibft -Iparsing
RM			= rm -rf

SRC_DIR		= src
PARSE_DIR	= parsing
SRC			= $(SRC_DIR)/gnl.c \
			  $(SRC_DIR)/map_loader.c \
			  $(SRC_DIR)/skybox.c \
			  $(SRC_DIR)/render_text.c \
			  $(SRC_DIR)/texture_wall.c \
			  $(SRC_DIR)/render.c \
			  $(SRC_DIR)/rays.c \
			  $(SRC_DIR)/rays_helpers.c \
			  $(SRC_DIR)/rays_helpers_utils.c \
			  $(SRC_DIR)/walls.c \
			  $(SRC_DIR)/walls_utils.c \
			  $(SRC_DIR)/dict.c \
			  $(SRC_DIR)/renderer.c \
			  $(SRC_DIR)/renderer_line.c \
			  $(SRC_DIR)/renderer_image.c \
			  $(SRC_DIR)/renderer_image_utils.c \
			  $(SRC_DIR)/setup.c \
			  $(SRC_DIR)/player.c \
			  $(SRC_DIR)/image_loader.c \
			  $(SRC_DIR)/free_and_exit.c \
			  $(PARSE_DIR)/parse_file.c \
			  $(PARSE_DIR)/parse_elements.c \
			  $(PARSE_DIR)/parse_texture.c \
			  $(PARSE_DIR)/parse_color.c \
			  $(PARSE_DIR)/parse_map.c \
			  $(PARSE_DIR)/parse_map_validate.c \
			  $(PARSE_DIR)/parse_utils.c \
			  $(PARSE_DIR)/parse_utils2.c \
			  main.c

OBJ_DIR		= obj
OBJ			= $(SRC:%.c=$(OBJ_DIR)/%.o)

LIBFT		= libft/libft.a

MLX_DIR		= minilibx/minilibx-linux
MLX_TGZ		= minilibx/minilibx-linux.tgz
LDFLAGS		= -L$(MLX_DIR) -lmlx_Linux -lX11 -lXext -lm

all: $(MLX_DIR) $(LIBFT) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -I$(MLX_DIR) $(OBJ) $(LIBFT) $(LDFLAGS) -o $(NAME)

$(MLX_DIR):
	tar -xzf $(MLX_TGZ) -C minilibx
	make -C $(MLX_DIR)

$(LIBFT):
	make -C libft

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(MLX_DIR) -c $< -o $@

clean:
	$(RM) $(OBJ_DIR)
	make -C libft clean
	@if [ -d "$(MLX_DIR)" ]; then make -C $(MLX_DIR) clean; fi

fclean: clean
	$(RM) $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re
