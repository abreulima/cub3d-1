NAME 	:= cub3d
CC		:= cc
CFLAGS 	:= -O3 -Wall -Werror -Wextra -I_inc
LDFLAGS := -Lminilibx-linux -lm -lmlx_Linux -lX11 -lXext  -g


CFILES	:=	_src/gnl.c \
			_src/map_loader.c \
			_src/skybox.c \
			_src/ft_itoa.c \
			_src/ft_strtok.c \
			_src/ft_strdup.c \
			_src/ft_strncmp.c \
			_src/ft_strcmp.c \
			_src/ft_strlen.c \
			_src/render_text.c \
			_src/texture_wall.c \
			_src/render.c \
			_src/rays.c \
			_src/walls.c \
			_src/dict.c \
			_src/renderer.c \
			_src/setup.c \
			_src/player.c \
			_src/ft_putstr.c \
			_src/ft_strstr.c \
			_src/ft_strlcpy.c \
			_src/ft_substr.c \
			_src/ft_strim.c \
			main.c

all: 
	${CC} ${CFLAGS} ${CFILES} -o ${NAME} ${LDFLAGS}